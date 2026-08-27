# ForgeEngine 0.1.0

> 🔨 Part of **Operation Blacksmith** — a self-driven initiative to build my own game dev tools from scratch (ForgeEngine, [PixelForge](#), ForgeStudio), then build my own games with them. This is engine #1: done, and it works.

A lightweight 2D game engine written in **C++17** with **SDL2**, built from scratch.

> 📹 [**Watch the ForgeEngine demo**] (I know its very low effort im working on a proper demo as well 🙂️)
>
> https://github.com/user-attachments/assets/cdcc1e6b-2c9e-46b0-b660-22159bd0b20c


ForgeEngine handles the boring, easy-to-get-wrong parts of making a 2D game — rendering, input, camera follow, physics, collision, Tiled map loading, audio, animation, and scene management — so you can focus on building the actual game.

## 🎯 Vision

ForgeEngine's long-term goal is to feel like **Pygame or LÖVE2D, but in C++**: a small, readable engine you can actually understand end-to-end, not a black box. Right now it's a solid, working v1 built by one person learning low-level systems programming — not yet a mature framework. Expect rough edges (see [Known Gaps](docs/API.md#known-gaps--rough-edges)), and expect them to shrink over time.

If you build something with it — a jam game, a prototype, anything — I'd genuinely love to see it. Open an issue, tag me, or just link it. That's the whole point of putting this out publicly.

**A note on how you'll actually use it today:** unlike Pygame/LÖVE2D (install as a package, code your game in a totally separate project), ForgeEngine is currently a single repo — you clone the whole thing, engine source included, and build your game alongside/inside `sandbox/`. Full source is visible because it's MIT licensed and genuinely meant to be read, not just consumed. Packaging ForgeEngine as a proper standalone library (link against it without touching engine internals) is on the roadmap below.

---

## ✨ Features

- **Rendering** — SDL2-backed renderer with a camera-relative coordinate system (world → screen transform baked in)
- **Camera** — smooth-follow camera with world-bounds clamping
- **Input** — keyboard state polling with `isKeyPressed` (single-frame) and `isKeyHeld` (continuous) distinction
- **Physics** — simple velocity/gravity body (`PhysicsBody`) with terminal velocity clamping
- **Collision** — AABB collider (`Collider`) with intersection tests
- **Entities** — base `Entity` class tying together sprite, collider, and physics body
- **Sprites & Animation** — texture-backed sprites with frame-based animation, flipping, and rotation
- **Tilemaps** — full [Tiled](https://www.mapeditor.org/) JSON map loading (tile layers + object layers), plus `.tsx` tileset parsing for solid-tile flags and animated tiles
- **Audio** — `SDL_mixer`-backed sound effects and music (channels, looping, volume control)
- **Text rendering** — `SDL_ttf`-backed text with color control
- **Asset management** — caching loader for textures and fonts, avoids duplicate loads
- **Scene management** — `SceneManager` handles scene lifecycle (load/update/draw) and clean scene transitions

## 🏗️ Architecture

```
Application
 ├── Window          (SDL_Window wrapper)
 ├── Renderer         (SDL_Renderer wrapper, camera-aware transforms)
 ├── Input            (keyboard state)
 ├── AudioManager      (SDL_mixer wrapper)
 └── SceneManager
      └── Scene (your game code)
           ├── Entity (Collider + PhysicsBody + Sprite)
           ├── Camera
           ├── TileMap
           └── AssetManager (Texture / Text cache)
```

- `Application` owns the main loop, delta time, and top-level systems (Window, Renderer, Input, Audio).
- `Renderer` transforms all draw calls through the active `Camera`, so game code always draws in **world space**.
- `Entity` is a minimal composition of `Collider` (AABB) + `PhysicsBody` (velocity/gravity) + `Sprite` (draw) — update it once per frame and it moves + collides consistently.
- `TileMap` loads Tiled `.json` exports directly (tile layers → render grid, object layers → spawn points/triggers), and separately parses `.tsx` XML for per-tile solidity + animation metadata.
- `AssetManager` caches `Texture`/`Text` by path so scenes can request the same asset repeatedly without reloading.
- `SceneManager` owns exactly one active `Scene` at a time and calls `Load()` on transition.

## 📦 Dependencies

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://github.com/libsdl-org/SDL_image)
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf)
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer)
- [nlohmann/json](https://github.com/nlohmann/json) (bundled/expected in `External/json.hpp`) — for Tiled `.json` parsing
- CMake ≥ 3.16
- A C++17 compiler (GCC/Clang)

### Install on Fedora/Nobara

```bash
sudo dnf install SDL2-devel SDL2_image-devel SDL2_ttf-devel SDL2_mixer-devel cmake
```

### Install on Ubuntu/Debian

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev cmake
```

### Install on Windows

The easiest path is [vcpkg](https://github.com/microsoft/vcpkg):

```powershell
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

.\vcpkg install sdl2 sdl2-image sdl2-ttf sdl2-mixer --triplet x64-windows
```

Then configure CMake to use vcpkg's toolchain file:

```powershell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

Alternatively, download the [SDL2 dev libraries](https://github.com/libsdl-org/SDL/releases) (and SDL2_image, SDL2_ttf, SDL2_mixer) manually, extract them, and point CMake at the include/lib paths yourself — vcpkg is just less manual work.

> Built and tested primarily on Linux (Nobara/Fedora) — Windows build path is not yet verified end-to-end. If you hit issues, please open one!

## 🚀 Building

```bash
git clone https://github.com/irfanAkhtar1/ForgeEngine.git
cd ForgeEngine

mkdir build && cd build
cmake ..
make
```

Run the sandbox demo:

```bash
./ForgeEngine
```

## 🧩 Quick Start

```cpp
#include "Application.h"
#include "Scene.h"

Application app;

class MyScene : public Scene {
public:
    void Load() override {
        // load assets, set up entities
    }

    void Update(float dt) override {
        // game logic
    }

    void Draw(Renderer& renderer) override {
        // draw calls
    }
};

int main() {
    if (!app.Init("My Game"))
        return -1;

    app.SetWorldSize(3200, 720);
    app.SetViewSize(1280, 720);

    SceneManager sceneManager;
    sceneManager.ChangeScene(new MyScene());

    app.Run([&](Renderer& renderer) {
        sceneManager.Update(app.GetDeltaTime());
        sceneManager.Draw(renderer);
    });

    app.ShutDown();
    return 0;
}
```

## 📁 Project Structure

```
ForgeEngine/
├── assets/          # Audio, Images, maps (Tiled .json/.tsx), tiles
├── include/         # Public headers
├── src/             # Engine implementation
├── sandbox/         # Demo game showcasing engine usage
├── CMakeLists.txt
└── arial.ttf
```

## 📚 Documentation

Full API reference with real method signatures: **[docs/API.md](docs/API.md)**

It also documents known gaps and rough edges honestly, rather than pretending they don't exist — check there before you spend an hour debugging something that's a known limitation.

## 🤝 Contributing

This is very much a living project. Contributions, bug reports, and "here's what confused me" issues are all welcome — especially if you're trying to build something with it and hit a wall. Some good first areas:

- Making a demo game (the best contribution — see what breaks!)
- Filling gaps in `docs/API.md` as the code evolves
- Tackling anything in the [Known Gaps](docs/API.md#known-gaps--rough-edges) list
- Windows/macOS build verification

No formal process yet — just open an issue or PR.

## 🗺️ Roadmap

- [ ] Package as a standalone library (link against ForgeEngine from your own project, Pygame/LÖVE2D-style)
- [ ] Wire `Sprite` (animation-capable) into `Entity` instead of raw `Texture`
- [ ] Multi-row spritesheet support for `Animation`
- [ ] `SceneManager` calling `Unload()` on scene transitions
- [ ] Basic ECS-style component system (currently a fixed `Entity` composition)
- [ ] More collision shapes beyond AABB
- [ ] Serialization for save/load state
- [ ] Verified Windows/macOS build instructions

## 📄 License

MIT — see [LICENSE](LICENSE)

## 🙋 About

Built by [Irfan](https://github.com/irfanAkhtar1) as part of **Operation Blacksmith** — a from-scratch game dev tooling initiative. ForgeEngine V1 is a completed learning milestone; a pixel art editor (**PixelForge**) and a lightweight DAW (**ForgeStudio**) are being built alongside it in the same pipeline. The end goal: build the tools, then build the games.
