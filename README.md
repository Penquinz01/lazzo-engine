# Lazzo Engine

A custom game engine built from scratch in C++ with an OpenGL 4.6 rendering backend, SDL3 windowing, and ImGui debug UI. Currently a work in progress.

---

## Current Features

- **SDL3 Window** — Native window creation with a properly initialized OpenGL 4.6 context
- **Main Loop** — Core engine loop with frame execution
- **Event System** — SDL events wrapped as engine events and dispatched to layers
- **Input System** — Unity-style polling with an observer pattern (`InputManager`)
- **Logging System** — Engine-level logging via spdlog
- **Layer System** — Stackable layers and overlays for scene and UI separation
- **3D Rendering** — Cube primitives with a material system, shaders, and transform support
- **Camera** — Unity-style camera with perspective / orthographic projection toggle and ImGui inspector
- **Lighting** — Directional, point, and spot lights with GLSL lighting shaders
- **ImGui Editor UI** — Runtime inspectors for cubes and camera

---

## Project Structure

```
Lazzo/        → Engine core (DLL: window, graphics, layers, events, input, objects)
SandBox/      → Test application (EXE, consumes Lazzo.dll)
vendor/       → Third-party dependencies (SDL3, GLAD, GLM, ImGui, spdlog, Assimp)
premake5.lua  → Build configuration
```

---

## Building

> ⚠️ **Windows only** — Cross-platform support is not yet implemented.

### Requirements

- Windows (Visual Studio recommended)
- [Premake5](https://premake.github.io/) (included in vendor/)

### Steps

```bash
# Clone the repo
git clone https://github.com/Penquinz01/lazzo-engine.git
cd lazzo-engine

# Generate project files
GenerateProject.bat

# Open Lazzo.slnx in Visual Studio and build
```

---

## Tech Stack

| Technology | Purpose                   |
| ---------- | ------------------------- |
| C++17      | Core engine language      |
| OpenGL     | Rendering backend (4.6)   |
| SDL3       | Window and input handling |
| ImGui      | Debug / editor UI         |
| GLM        | Math library              |
| spdlog     | Logging                   |
| Premake5   | Build system              |

---

## Roadmap

### In Progress

- [ ] Unify the raw-GL cube path with the abstract graphics pipeline
- [ ] Wire `ObjectRenderer` into the render loop

### Planned

- [ ] ECS (Entity Component System) — Data-driven architecture for game objects
- [ ] Material/Editor workflow — Better shader and material tooling
- [ ] Model import — Assimp is linked but not yet used in code
- [ ] Animation System — Skeletal and sprite-based animation support
- [ ] Physics Integration — [Jolt Physics](https://github.com/jrouwe/JoltPhysics) for rigid body simulation
- [ ] Cross-platform Support — Linux and macOS compatibility

---

## License

Apache 2.0 — see [LICENSE](LICENSE) for details.