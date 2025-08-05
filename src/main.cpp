#include "raylib.h"
#include <vector>
#include <cmath>
#include <string>

class Particle{
    private:
    Vector2 position;
    Vector2 velocity;
    float life;
    float maxLife;
    Color baseColor;
    std::vector<Vector2> trail;
    static const int MAX_TRAIL_LENGTH = 10;
    static const float GRAVITY;

    public:
    Particle(Vector2 startPos, Vector2 startVel, float startLife, Color startColor){
        position = startPos;
        velocity = startVel;
        life = startLife;
        maxLife = startLife;
        baseColor = startColor;
        trail.push_back(position);
    }

    void Update(float deltaTime){
        trail.push_back(position);
        if (trail.size() > MAX_TRAIL_LENGTH)
        {
            trail.erase(trail.begin());
        }
        
        velocity.y += GRAVITY * deltaTime;

        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;

        life -= deltaTime;
    }

    void Draw(){

        float lifeRatio = life/maxLife;

        // Color currentColor = baseColor;

        // if(lifeRatio > 0.5){
        //     float t = (lifeRatio - 0.5) * 2.0f;

        //     currentColor = (Color){static_cast<unsigned char>(baseColor.r * t+ 255 * (1-t)),static_cast<unsigned char>(baseColor.g * t), static_cast<unsigned char>(baseColor.b * t), 255};

        // } else{
        //     float alpha = lifeRatio * 2.0f;
        //     currentColor = (Color){255,0,0,static_cast<unsigned char>(255 * alpha)};
        // }

        for (size_t i = 1; i < trail.size(); i++)
        {
            float trailAlpha = (static_cast<float>(i)/static_cast<float>(trail.size())) * lifeRatio;

            Color trailColor = baseColor;
            trailColor.a = static_cast<unsigned char>(100 * trailAlpha);

            DrawLineEx(trail[i-1], trail[i], 2.0f, trailColor);

        }
        
        Color currentColor = baseColor;
        currentColor.a = static_cast<unsigned char>(255 * lifeRatio);

        float currentSize = 4.0f * lifeRatio;

        DrawCircleV(position, currentSize, currentColor);
    }

    bool isAlive(){
        return life > 0.0f;
    }
};


void CreateExplosion(std::vector<Particle> &particles, Vector2 center, int particleCount){
    
    Color colors[] = {YELLOW, RED, ORANGE, WHITE, GOLD, LIME, PINK, SKYBLUE};
    int colorCount = 8;

    for (int i = 0; i < particleCount; i++)
    {
        float angle = GetRandomValue(0,360) * DEG2RAD;

        float speed = GetRandomValue(50,250);

        Vector2 velocity = {static_cast<float>(cos(angle) * speed), static_cast<float>(sin(angle) * speed)};

        Color randomColor = colors[GetRandomValue(0, colorCount - 1)];

        particles.push_back(Particle(center, velocity, GetRandomValue(20,40)/10.0f, randomColor));

    }
    
}

void createFountain(std::vector<Particle> &particles, Vector2 center, int particleCount){
    Color colors[] = {YELLOW, GOLD, ORANGE};

    for (int i = 0; i < particleCount; i++)
    {
        float angle = GetRandomValue(-45,45) * DEG2RAD - PI/2;
        float speed = GetRandomValue(100,600);

        Vector2 velocity = {static_cast<float>(cos(angle) * speed), static_cast<float>(sin(angle) * speed)};
        Color randomColor = colors[GetRandomValue(0,2)];

        particles.push_back(Particle(center, velocity, GetRandomValue(30,50)/10.0f, randomColor));

    }
    
}

void createSpiral(std::vector<Particle> &particles, Vector2 center, int particleCount){
    for (int i = 0; i < particleCount; i++)
    {
        float angle = (static_cast<float>(i)/ static_cast<float>(particleCount)) * 4.0f * PI;
        float speed = GetRandomValue(80,150);

        Vector2 velocity {static_cast<float>(cos(angle)*speed), static_cast<float>(sin(angle)*speed)};

        particles.push_back(Particle(center, velocity, GetRandomValue(25, 35)/ 10.0f, PURPLE));

    }
    
}

const float Particle::GRAVITY = 400.0f;

int main(){

    InitWindow(800, 600, "Fireworks");
    SetTargetFPS(60);

    std::vector<Particle> particles;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePos = GetMousePosition();

            CreateExplosion(particles, mousePos, 250);
        }

        if(IsKeyPressed(KEY_F)){
            Vector2 center = {400, 500};
            createFountain(particles, center, 250);
        }

        if(IsKeyPressed(KEY_S)){
            Vector2 mousePos = GetMousePosition();
            createSpiral(particles, mousePos, 200);
        }

        for (size_t i = 0; i < particles.size(); i++)
        {
            particles[i].Update(deltaTime);
        }

        for (size_t i = particles.size(); i-- > 0;)
        {
            if (!particles[i].isAlive())
            {
                particles.erase(particles.begin() + i);
            }
            
        }
        
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Fireworks", 10, 10, 20, WHITE);
        DrawText(("Particles: " + std::to_string(particles.size())).c_str(), 10, 40, 20, WHITE);
        
        for(auto& particle : particles){
            particle.Draw();
        }

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}