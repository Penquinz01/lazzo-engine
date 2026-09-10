# AGENTS.md — Lazzo Engine

## Overview

Lazzo is a C++ game engine built on OpenGL 4.6 with SDL3 windowing and ImGui
debug UI. It ships as a DLL (`Lazzo`) consumed by a test client (`SandBox`).
The build system is Premake5 generating Visual Studio solutions (currently
Windows/x64 only).

---

## Directory Layout

```
Lazzo/                        Root
├── premake5.lua              Workspace + project definitions
├── GenerateProject.bat       Runs premake5.exe vs2026
├── Lazzo.slnx                Visual Studio solution
├── vendor/
│   ├── premake/              Premake5 binary
│   └── (submodules: spdlog)
├── Lazzo/                    Engine shared library project
│   ├── Lazzo.vcxproj
│   ├── Shaders/
│   │   └── OpenGL/           GLSL 460 shaders (Basic.vert, Basic.frag)
│   └── src/
│       ├── lzpch.h           Precompiled header (STL + Windows.h)
│       ├── lzpch.cpp         PCH compilation unit
│       ├── Lazzo.h           Public engine header (includes Application, Layer, Log, EntryPoint)
│       └── Lazzo/
│           ├── Core.h         LAZZO_API export/import macro, BIT macro
│           ├── Application.h/cpp   Engine class — owns Window, runs main loop
│           ├── EntryPoint.h   main() — calls CreateApplication() + Run()
│           ├── Log.h/cpp      spdlog wrappers (LZ_CORE_*, LZ_* macros)
│           ├── Window/
│           │   ├── Window.h/cpp             SDL3 window + OpenGL context lifecycle
│           │   ├── GraphicsFactory.h        (empty placeholder)
│           │   ├── GraphicsAPI/
│           │   │   ├── GraphicsAPI.h        Abstract base + GraphicAPI enum
│           │   │   ├── OpenGLAPI.h/cpp      OpenGL context init/shutdown
│           │   │   ├── Shader.h             Abstract Shader + static Create factory
│           │   │   ├── ShaderFileData.h     Vertex/fragment path pair
│           │   │   ├── VertexBuffer.h       Abstract VBO + static Create factory
│           │   │   ├── VertexBufferLayout.h Element description + stride calculator
│           │   │   ├── VertexArray.h        Abstract VAO + static Create factory
│           │   │   ├── IndexBuffer.h        Abstract IBO + static Create factory
│           │   │   ├── Renderer.h           Abstract Renderer + static Create factory
│           │   │   ├── Material.h           Wraps Shader; owns uniform setters
│           │   │   └── OpenGL/              Concrete OpenGL 4.6 implementations
│           │   │       ├── OpenGL.h         Convenience include-all
│           │   │       ├── Shader.h/cpp
│           │   │       ├── VertexBuffer.h/cpp
│           │   │       ├── VertexArray.h/cpp
│           │   │       ├── IndexBuffer.h/cpp
│           │   │       └── Renderer.h/cpp
│           │   ├── UI/
│           │   │   └── ImguiUI.h/cpp       ImGui init, frame begin/end, SDL event passthrough
│           │   └── Events/
│           │       ├── Event.h              Base Event class + EventDispatcher
│           │       ├── Events.h             Convenience include-all
│           │       └── KeyDownEvent.h/cpp   Keyboard event wrapper
│           ├── Layers/
│           │   ├── Layer.h/cpp             Abstract layer (OnAttach/OnDetach/OnUpdate/OnEvent)
│           │   └── LayerStack.h/cpp        Ordered vector; overlays after layers
│           ├── Primitives/
│           │   ├── Primitives.h            Base class with transform + Material
│           │   └── Cube.h/cpp              Hardcoded cube mesh + immediate-mode GL
│           ├── Object/
│           │   ├── Object.h                Convenience include
│           │   ├── GameObject.h            Abstract game object (position/rotation/scale)
│           │   ├── ObjectRenderer.h/cpp    Binds VBO/VAO/IBO/Shader for a draw call
│           │   ├── Camera/
│           │   │   ├── Camera.h            Abstract camera interface (interfaces identical to GraphicsAPI pattern)
│           │   │   └── PerspectiveCamera.h/cpp   Concrete FPS-style camera; GetViewMatrix/GetProjectionMatrix; DrawUI
│           │   └── Lights/
│           │       └── Light.h             Base light class + LightType enum
│           └── Utilities/
│               ├── Utilities.h             Convenience include
│               ├── Info.h                  Singleton — stores chosen GraphicAPI
│               ├── Vector.h/cpp            Custom Vector3 (unused by rest of engine)
└── SandBox/                  Client application project
    ├── Sandbox.vcxproj
    └── src/
        └── SandboxApp.cpp    Subclasses Application; creates a Cube
```

---

## Architecture

### Two-Project Workspace

| Project  | Kind       | Purpose                                      |
|----------|------------|----------------------------------------------|
| Lazzo    | SharedLib  | Engine runtime — window, graphics, layers, UI |
| SandBox  | ConsoleApp | Test harness — subclasses `Lazzo::Application` |

### Application Lifecycle

1. `main()` in `EntryPoint.h` calls `Lazzo::CreateApplication()` (user-defined).
2. `Application` constructor creates a `Window` (SDL3 + OpenGL 4.6 context).
3. `Application::Run()` delegates to `Window::OnUpdate()` which owns the
   infinite main loop: poll SDL events → clear → renderScene() → renderUI() →
   swap.
4. `OnRender()` and `OnImGuiRender()` are virtual hooks overridden by the client.

### Graphics API Abstraction

```
GraphicsAPI (abstract)           Lazzo/Window/GraphicsAPI/GraphicsAPI.h
  └─ OpenGLAPI                   Lazzo/Window/GraphicsAPI/OpenGLAPI.h

Graphics resources (abstract)    Lazzo/Window/GraphicsAPI/
  ├─ Shader            ←── OpenGL::Shader
  ├─ VertexBuffer      ←── OpenGL::VertexBuffer
  ├─ VertexArray       ←── OpenGL::VertexArray
  ├─ IndexBuffer       ←── OpenGL::IndexBuffer
  └─ Renderer          ←── OpenGL::OpenGLRenderer
```

- Abstract classes live in `Lazzo/Window/GraphicsAPI/`.
- Concrete OpenGL implementations live in the `OpenGL/` subdirectory.
- Each abstract resource has a `static std::unique_ptr<T> Create(...)` factory
  method that constructs the OpenGL variant. This is the **only** mechanism for
  creating GPU resources; clients never `new` a concrete type directly.
- `Material` wraps a `Shader` and exposes uniform setters.
- `ObjectRenderer` assembles a full draw call (VBO + VAO + IBO + Shader).

### Window & UI

- `Window` owns the `SDL_Window`, the `GLContext`, and an `ImguiUI` instance.
- `ImguiUI` manages the ImGui context lifecycle and per-frame begin/end.
- `GraphicAPI` enum (`OpenGL`, `Vulkan`, etc.) is stored in
  `Lazzo::Utilities::Info` singleton, though currently hardcoded to OpenGL.

### Event System

- `Event` base class with `GetEventType()` and a `handled` flag.
- `EventDispatcher` uses template dispatch to route events by type.
- Concrete events (e.g. `KeyDownEvent`) wrap raw `SDL_Event` data.
- Events are polled in `Window::OnUpdate()` and dispatched to layers.

### Layer System

- `Layer` base with virtual hooks: `OnAttach`, `OnDetach`, `OnUpdate`, `OnEvent`.
- `LayerStack` holds layers in a `vector` with an insertion iterator — layers
  go before overlays; overlays go at the end.
- `Application::PushLayer()` / `PushOverlay()` add to the stack.

### Primitives & Objects

- `Primitives` base provides transform (position/rotation/scale) and a
  `Material`. Currently sets up raw GL VAO/VBO in subclasses.
- `GameObject` is a separate abstract class with the same transform fields.
- `Cube` multiply-inherits both and provides `Draw()` / `DrawUI()` using
  hardcoded vertex data and immediate-mode GL calls (not using the abstract
  graphics pipeline).
- `ObjectRenderer` is a newer path that uses the abstract VBO/VAO/IBO/Shader
  factories but is not yet wired into the layer/render loop.
- `Camera` is an abstract interface (`Lazzo::Object::Camera::Camera`);
  `PerspectiveCamera` implements `GetViewMatrix()` (Euler pitch/yaw/roll
  matching `Cube`'s rotation order) and `GetProjectionMatrix()` (GLM
  perspective). `Cube::Draw()` takes a `const Camera&` and uploads
  `u_Model`/`u_View`/`u_Projection`. Use the interface + `LAZZO_API` types for
  drawing code; ImGui inspectors live in the DLL (`DrawUI()`).

---

## Naming & Coding Conventions

### General

- **Language standard**: C++17 (`cppdialect "C++17"`).
- **Platform**: Windows-only (`LZ_PLATFORM_WINDOWS`). Cross-platform `#error`
  guard in `Core.h`.

### Namespaces

| Namespace                 | Contents                              |
|---------------------------|---------------------------------------|
| `Lazzo`                   | Core engine (Application, Window, Layer, Primitives) |
| `Lazzo::Graphics`         | Abstract GPU resources (Shader, VBO, VAO, etc.) |
| `Lazzo::OpenGL`           | Concrete OpenGL implementations       |
| `Lazzo::Graphics::OpenGL` | OpenGLRenderer specifically           |
| `Lazzo::Object`           | GameObject, ObjectRenderer            |
| `Lazzo::Object::Lights`   | Light, LightType                      |
| `Lazzo::Utilities`        | Info singleton, Vector3               |

### Class / Type Names

- PascalCase: `Application`, `KeyDownEvent`, `VertexBufferLayout`, `OpenGLAPI`.

### Member Variables

- Prefixed `m_`: `m_Window`, `m_RendererID`, `m_LayerStack`, `m_Material`.
- Static members prefixed `s_`: `s_CoreLogger`, `s_ClientLogger`.

### Methods

- PascalCase: `Run()`, `OnUpdate()`, `Bind()`, `GetEventType()`, `PushLayer()`.
- Getters prefixed `Get` or plain name: `GetName()`, `GetPosition()`.
- One-off pattern: `ReturnScanCode()` (non-standard; prefer `GetScanCode()`).

### Enums

- `enum class` only: `GraphicAPI::OpenGL`, `EventType::KeyDown`,
  `LightType::Point`.

### Macros / Defines

- Engine prefix `LZ_`: `LZ_PLATFORM_WINDOWS`, `LZ_BUILD_DLL`, `LZ_DEBUG`,
  `LZ_RELEASE`, `LZ_DIST`.
- Log macros: `LZ_CORE_ERROR(...)`, `LZ_WARN(...)`, etc.
- Utility: `BIT(x)`.
- Export: `LAZZO_API` (`__declspec(dllexport/dlimport)`).

### File Organization

- One primary class per file, file named after the class: `Shader.h` /
  `Shader.cpp`.
- `#pragma once` for all headers.
- Every `.cpp` includes `"lzpch.h"` as the first line.
- Header aggregation files named in plural or by concept: `Events.h`,
  `Primitives.h`, `Utilities.h`, `OpenGL.h`.
- Abstract base in parent directory, concrete in `OpenGL/` subdirectory.

### Include Paths

- Engine headers use `"Lazzo/..."` relative to `Lazzo/src/`.
- OpenGL implementations reference abstract headers via full path:
  `"Lazzo/Window/GraphicsAPI/Shader.h"`.
- Third-party headers are angle-bracketed: `<glad/glad.h>`, `<glm/glm.hpp>`,
  `<spdlog/spdlog.h>`, `<imgui.h>`.
- SDL3 is angle-bracketed: `"SDL3/SDL.h"`.

### Smart Pointers

- `std::unique_ptr` for ownership of Window, ImGuiUI, GPU resources.
- `std::shared_ptr` for spdlog loggers.
- Factory methods return `std::unique_ptr<Base>`.

---

## Build Commands

### Generate Project Files

```bat
GenerateProject.bat
```

Runs `vendor\premake\premake5.exe vs2026` to regenerate the Visual Studio
solution and project files.

### Build

Open `Lazzo.slnx` in Visual Studio and build, or use:

```bat
msbuild Lazzo.slnx /p:Configuration=Debug /p:Platform=x64
```

### Configurations

| Config  | Defines        | Optimization |
|---------|----------------|--------------|
| Debug   | `LZ_DEBUG`     | Off (symbols) |
| Release | `LZ_RELEASE`  | On           |
| Dist    | `LZ_DIST`     | On           |

### Output Layout

```
bin/<Config>-windows-x86_64/
  ├── Lazzo/      Lazzo.dll, Lazzo.pdb
  └── SandBox/    SandBox.exe, Lazzo.dll, SDL3.dll
bin-int/<Config>-windows-x86_64/
  ├── Lazzo/      Intermediate .obj files
  └── SandBox/    Intermediate .obj files
```

---

## Third-Party Dependencies

| Library   | Location                     | Purpose            |
|-----------|------------------------------|--------------------|
| SDL3      | `Lazzo/vendor/SDL3/`        | Windowing, input   |
| OpenGL    | `Lazzo/vendor/glad/`        | GL 4.6 loader      |
| GLM       | `Lazzo/vendor/glm/`         | Math (vectors/mats)|
| ImGui     | `Lazzo/vendor/imgui/`       | Debug UI           |
| spdlog    | `Lazzo/vendor/spdlog/`      | Logging            |
| Assimp    | `Lazzo/vendor/assimp/`      | 3D model import (lib linked, not yet used in code) |

---

## Known Patterns & Quirks

- `Cube` bypasses the abstract graphics pipeline (raw GL calls) while
  `ObjectRenderer` uses the abstract factories. These are two parallel
  approaches that will likely converge.
- `GraphicsFactory.h` is an empty placeholder.
- `Utilities::Vector3` is a custom vector type not used elsewhere; the engine
  uses GLM throughout.
- `ImGui` backend files are compiled directly into the engine DLL (not as a
  separate library).
- Precompiled header `lzpch.h` is included in every `.cpp` but includes only
  STL and `Windows.h`.
- The `Window` class contains both SDL lifecycle management and the full main
  loop (event polling, clear, render, swap) in `OnUpdate()`.
- Shaders are loaded from relative paths (`../Lazzo/Shaders/...`) which depends
  on the working directory at runtime.
