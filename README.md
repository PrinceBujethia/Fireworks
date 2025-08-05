
🎆 **Raylib Particle Fireworks**

![C++](https://img.shields.io/badge/C%2B%2B-11%2B-blue?style=for-the-badge) ![raylib](https://img.shields.io/badge/raylib-4.x-black?style=for-the-badge) ![platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=for-the-badge) ![license](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)

A real-time fireworks simulator written in modern C++ with Raylib.
Built from scratch to showcase clean OOP design, mathematically-driven visuals, and robust engineering practices valued by professionals and recruiters.

---

✨ **Features**

**Architecture:**
- Class-based (`Particle`) encapsulating physics, rendering, and life-cycle
- Self-contained update/render loop with delta-time integration
- Efficient memory management (particles and trails)

**Visuals:**
- Radial explosions, spirals, and fountains
- Particle trails with alpha fading
- Dynamic color transitions (base → red → transparent)
- Size scaling over lifetime

**Math & Physics:**
- Gravity and velocity updates each frame
- Trigonometric angle→vector conversion
- Linear interpolation for color and size

**Performance:**
- Trail length limit
- Backwards vector erasure for removal
- No heap allocation inside the frame loop

**Controls:**
- **Left Click:** Radial explosion at mouse
- **F key:** Fountain effect
- **S key:** Spiral pattern

---

🏗️ **Project Structure**

```
fireworks/
├─ src/
│  ├─ main.cpp          # entry point and game loop
│  └─ particle.hpp/cpp  # Particle class for physics and rendering
├─ CMakeLists.txt       # optional CMake build config
└─ README.md
```

---

🔧 **Build & Run**

**Step 1: Install Raylib**

```bash
# Debian / Ubuntu
sudo apt install libraylib-dev

# macOS (Homebrew)
brew install raylib

# Windows (MSYS2)
pacman -S mingw-w64-x86_64-raylib
```

**Step 2: Compile**

```bash
# Linux / macOS
g++ -std=c++11 src/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o fireworks

# Windows (MinGW)
g++ -std=c++11 src/*.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -o fireworks.exe
```

Or, with CMake:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

**Step 3: Run**

```bash
./fireworks
```

---

🔍 **Code Highlights**

| Step | Concept         | Example Code/Logic                                 |
|------|----------------|----------------------------------------------------|
| 1.   | Particle Class | constructor sets position, velocity, life, baseColor|
| 2.   | Physics Update | `velocity.y += GRAVITY * dt; position += velocity * dt;` |
| 3.   | Trail Capture  | push current position, trim to MAX_TRAIL_LENGTH    |
| 4.   | Colour Transition | if lifeRatio>0.5 interpolate to red, else fade alpha |
| 5.   | Patterns       | Explosion, spiral, fountain use trig for vectors   |

---

🎯 **Why This Project Matters**

- Game-ready techniques: Demonstrates core game engine and graphics concepts
- Math competence: Shows trigonometry, interpolation, and delta-time animation
- Clean engineering: Readable, modular, and efficient (SOLID-inspired)
- Recruiter appeal: Focus on modern C++ design, graphics, real-time logic, and code quality

---

🗺️ **Roadmap**

- Starfield background with twinkling effect
- Vertical gradient night sky
- Sound effects (explosion crackle, launch whistle)
- Configurable JSON-based firework presets
- GPU sprite-based particles (performance boost)
- 3D camera & depth-sorted particles

---

🤝 **Contributing**

Pull requests are welcome—especially for new explosion patterns, performance tips, or bug fixes.
Feel free to open issues for suggestions!
