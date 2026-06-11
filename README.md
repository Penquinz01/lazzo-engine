# Lazzo Engine

A custom game engine built from scratch in C++ with an OpenGL rendering backend. Currently a work in progress.

---

## Current Features

- **SDL Window** — Native window creation with a properly initialized OpenGL context
- **Main Loop** — Core engine loop with frame execution
- **Event System** — Handles input and window events via SDL
- **Logging System** — Engine-level logging for debugging and runtime info

---

## Project Structure

```
Lazzo/        → Engine core (window, loop, events, logging)
SandBox/      → Test application (WIP)
vendor/       → Third-party dependencies (Premake)
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

# Open Lazzo.sln in Visual Studio and build
```

---

## Roadmap

### In Progress

- [ ] Layer System — Stackable layers for UI, game logic separation
- [ ] Sandbox Application — Test environment for engine features

### Planned

- [ ] ECS (Entity Component System) — Data-driven architecture for game objects
- [ ] Rendering System — 2D/3D renderer built on the OpenGL backend
- [ ] Lighting System — Basic ambient, directional, and point lights
- [ ] Animation System — Skeletal and sprite-based animation support
- [ ] Physics Integration — [Jolt Physics](https://github.com/jrouwe/JoltPhysics) for rigid body simulation
- [ ] Cross-platform Support — Linux and macOS compatibility

---

## Tech Stack

| Technology               | Purpose                   |
| ------------------------ | ------------------------- |
| C++                      | Core engine language      |
| OpenGL                   | Rendering backend         |
| SDL2                     | Window and input handling |
| Premake5                 | Build system              |
| Jolt Physics _(planned)_ | Physics simulation        |

---

## License

Apache 2.0 — see [LICENSE](LICENSE) for details.
