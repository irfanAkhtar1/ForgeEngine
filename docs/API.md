# ForgeEngine API Reference

Real signatures pulled directly from `include/`. This is a reference, not a tutorial — see the main [README](../README.md) for a quick-start walkthrough.

> 📌 This doc is written by hand and may drift from the code over time. If something here doesn't match `include/`, trust the header and open an issue/PR.

---

## Table of Contents

- [Application](#application)
- [Window](#window)
- [Renderer](#renderer)
- [Camera](#camera)
- [Input](#input) / [Key](#key)
- [Scene](#scene) / [SceneManager](#scenemanager)
- [Entity](#entity)
- [Collider](#collider)
- [PhysicsBody](#physicsbody)
- [Sprite](#sprite)
- [Animation](#animation)
- [Texture](#texture)
- [Text](#text)
- [AssetManager](#assetmanager)
- [AudioManager](#audiomanager)
- [TileMap](#tilemap)

---

## Application

The engine entry point. Owns the window, renderer, input, audio, and the main loop.

```cpp
bool Init(const char* title);
void SetWorldSize(int width, int height);
void SetViewSize(int width, int height);
void SetViewportSize(int width, int height);
void Run(std::function<void(Renderer&)> drawCallback);
void SetColor(int r, int g, int b, int a = 255);
void ShutDown();

Input&        GetInput();
Renderer&     GetRenderer();
AudioManager& GetAudio();
SDL_Window*   GetSDLWindow() const;

float GetDeltaTime() const;

int GetWorldWidth() const;
int GetWorldHeight() const;
int GetViewWidth() const;
int GetViewHeight() const;
int GetViewportWidth() const;
int GetViewportHeight() const;
```

**Notes**
- `SetWorldSize` = total playable world in world units. `SetViewSize` = the camera's visible area (logical render size). `SetViewportSize` = actual window pixel size. These three are independent — this is what lets you have a 320×180 pixel-art world scaled up to a 1280×720 window.
- `Run()` takes your draw callback and drives the loop: polls events, updates `Input`, computes `deltaTime`, clears the screen, calls your callback, presents.
- Defaults: world/view = 320×180, viewport = 1280×720.

---

## Window

Thin wrapper around `SDL_Window`.

```cpp
bool Create(const char* title, int width, int height);
void Destroy();
void Resize(int width, int height);

SDL_Window* GetSDLWindow() const;
int GetWidth() const;
int GetHeight() const;
```

---

## Renderer

Wraps `SDL_Renderer`. All draw coordinates pass through `TransformX`/`TransformY`, which offset by the active `Camera` — so game code always thinks in **world space**, never screen space.

```cpp
bool Create(SDL_Window* window);
void Destroy();

void SetCamera(Camera* cam);
Camera* GetCamera() const;

SDL_Renderer* GetSDLRenderer() const;

void SetColor(int r, int g, int b, int a = 255);
void Clear();

void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a = 255);

int TransformX(float x) const;
int TransformY(float y) const;

void SetWorldSize(int width, int height);
void SetViewSize(int width, int height);
void SetViewportSize(int width, int height);
```

**Notes**
- `SetViewSize` calls `SDL_RenderSetLogicalSize` internally — this is what handles resolution-independent scaling.
- If no camera is set, `TransformX`/`TransformY` return the input coordinate unchanged (no offset).

---

## Camera

Smooth-follow camera with world-bounds clamping.

```cpp
Camera(int width, int height);

void Follow(float targetX, float targetY, float smoothness);
void SetPosition(float x, float y);

void SetViewSize(int width, int height);
void SetWorldSize(int width, int height);

float GetX() const;
float GetY() const;
int GetViewWidth() const;
int GetViewHeight() const;
```

**Notes**
- `Follow()` lerps toward the target (`smoothness` is a 0–1 factor per call, higher = snappier) and clamps the camera to `[0, worldSize - viewSize]` so it never shows past the map edge. If the world is smaller than the view on an axis, that axis locks to `0`.
- `SetPosition()` centers the camera directly on a point (no smoothing, no clamping).

---

## Input / Key

Keyboard polling with separate "just pressed" vs "held" states.

```cpp
// Input
Input();  // captures initial SDL keyboard state
void Update();
bool isKeyHeld(Key key);
bool isKeyPressed(Key key);
```

```cpp
// Key.h — enum class Key
A–Z, Num0–Num9, Up, Down, Left, Right,
Space, Enter, Escape, Tab, Backspace,
LShift, RShift, LCtrl, RCtrl, LAlt, RAlt,
F1–F12
```

**Notes**
- Call `Update()` once per frame (Application does this for you inside `Run()`).
- `isKeyPressed` is true only on the frame the key transitions from up → down. `isKeyHeld` is true every frame the key is down.
- `ToSDLScancode(Key)` (free function in `Key.h`) maps the enum to `SDL_Scancode` if you need raw SDL interop.

---

## Scene / SceneManager

Your game's screens/states. `Scene` is a pure interface — implement all four methods.

```cpp
// Scene (abstract)
virtual void Load() = 0;
virtual void Update(float dt) = 0;
virtual void Draw(Renderer& renderer) = 0;
virtual void Unload() = 0;
```

```cpp
// SceneManager
void ChangeScene(Scene* newScene);
void Update(float dt);
void Draw(Renderer& renderer);
```

**Notes**
- `SceneManager` takes ownership of scenes passed to `ChangeScene` — it deletes the old scene and calls `Load()` on the new one. Pass `new YourScene()`, don't manage the pointer yourself.
- ⚠️ Known gap: `SceneManager::ChangeScene` calls `Load()` on the new scene but does **not** currently call `Unload()` on the outgoing scene before deleting it — if your `Unload()` does cleanup you rely on, call it manually before switching for now.

---

## Entity

Base class composing a sprite, collider, and physics body. Extend this for game objects.

```cpp
virtual ~Entity() = default;
virtual void Update(float dt);   // advances body, moves collider by velocity * dt
virtual void Draw(Renderer& renderer);

void SetPosition(float x, float y);

Collider& GetCollider();
const Collider& GetCollider() const;

// Public members
Texture sprite;      // NOTE: currently typed Texture, not Sprite — see caveat below
Collider collider;
PhysicsBody body;

protected:
int width = 16;
int height = 16;
```

**Notes**
- ⚠️ `Entity::sprite` is declared as `Texture`, not `Sprite` — despite the engine having a full `Sprite` class with animation support. `Entity::Draw()` calls `sprite.Draw(renderer, x, y, width, height)`, using `Texture`'s overload, so **animated entities need custom `Draw()` overrides** for now (bypass the base member or subclass around it). This is a known rough edge, not a bug in your game code.
- Override `Update`/`Draw` in subclasses to add custom behavior — call the base version first if you still want physics/collision movement.

---

## Collider

Simple AABB (axis-aligned bounding box).

```cpp
Collider() = default;
Collider(float x, float y, float w, float h);

void SetPosition(float x, float y);
void SetSize(float w, float h);

bool Intersects(const Collider& other) const;

float GetX() const;
float GetY() const;
float GetWidth() const;
float GetHeight() const;

bool IsDestroyed() const;
void Destroy();
```

**Notes**
- `Destroy()`/`IsDestroyed()` just flip a flag — the collider doesn't remove itself from anything. It's on you to check `IsDestroyed()` in your own entity-cleanup logic.

---

## PhysicsBody

Velocity + gravity integrator. No collision resolution built in — pair it with `Collider::Intersects` yourself.

```cpp
void Update(float dt);   // applies gravity, clamps to terminal velocity

void SetVelocity(float vx, float vy);
void AddVelocity(float vx, float vy);

float GetVelocityX() const;
float GetVelocityY() const;

void SetVelocityX(float vx);
void SetVelocityY(float vy);

void SetGravity(float grv);
void SetTerminalVelocity(float velocity);
```

**Defaults:** `gravity = 1800.0f`, `terminalVelocity = 800.0f` (world units/sec — tune per your world scale).

---

## Sprite

Texture/animation-backed drawable with position, rotation, and flip. (Note: not currently wired into `Entity` — see [Entity caveat](#entity).)

```cpp
void SetTexture(Texture& texture);
void SetAnimation(Animation& animation);

void SetPosition(float x, float y);
void SetSize(float width, float height);
void SetRotation(double angle);
void SetFlip(SDL_RendererFlip flip);

void FlipHorizontal();
void FlipVertical();
void ResetFlip();

void Draw(Renderer& renderer);

float GetX() const;
float GetY() const;
float GetWidth() const;
float GetHeight() const;
double GetRotation() const;
Animation* GetAnimation() const;
```

**Notes**
- If `SetAnimation()` is used, `Draw()` sources the current animation frame's sub-rect from the texture automatically (via `Animation::GetFrameX/Y/Width/Height`). Without an animation set, it draws the whole texture.

---

## Animation

Frame-based sprite-sheet animation (single row only — see caveat).

```cpp
void SetTexture(Texture& texture);
void SetFrame(int width, int height);   // per-frame pixel size
void SetFrameCount(int count);
void SetFPS(float fps);

void Update(float dt);
void Reset();

int GetFrameX() const;
int GetFrameY() const;
int GetFrameWidth() const;
int GetFrameHeight() const;

Texture* GetTexture() const;
int GetCurrFrame() const;
```

**Defaults:** `fps = 8.0f`, `totalFrame = 1`.

**Notes**
- ⚠️ `GetFrameY()` always returns `0` — animations currently only support horizontal single-row spritesheets. Multi-row sheets aren't supported yet.

---

## Texture

Raw image wrapper (`SDL_Texture`). Used directly by `Entity::sprite` and internally by `Sprite`.

```cpp
bool Load(Renderer& renderer, const char* path);

bool Draw(Renderer& renderer, float x, float y, float width, float height,
          double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

bool Draw(Renderer& renderer, float x, float y, float width, float height,
          int srcX, int srcY, int srcW, int srcH,
          double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);

void Destroy();

int GetWidth() const;
int GetHeight() const;
```

**Notes**
- Second `Draw()` overload takes a source rect — this is what `Animation`/`TileMap` use to blit sub-regions of a spritesheet/tileset.

---

## Text

`SDL_ttf`-backed text rendering.

```cpp
bool Load(Renderer& renderer, const char* fontPath, int fontSize);
bool Draw(Renderer& renderer, const char* text, int x, int y);
void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
void Destroy();
```

**Default color:** white (`255,255,255,255`).

**Notes**
- ⚠️ `Draw()` creates and destroys a new `SDL_Texture` from the rendered surface **every call** — fine for occasional UI text, but avoid calling this every frame for large amounts of text without caching if you hit performance issues.

---

## AssetManager

Path-keyed cache for `Texture` and `Text`, so repeated loads of the same asset are free after the first.

```cpp
Texture& LoadTexture(Renderer& renderer, const std::string& path);
Texture& GetTexture(const std::string& path);

Text& LoadFont(Renderer& renderer, const std::string& path, int size);
Text& GetFont(const std::string& path, int size);

void Destroy();
```

**Notes**
- `GetTexture`/`GetFont` **throw `std::runtime_error`** if the asset hasn't been loaded yet — always `Load*` before `Get*`, or wrap in try/catch.
- Fonts are cached by `path:size`, so the same font file at different sizes gets separate cache entries (as expected for TTF rendering).

---

## AudioManager

`SDL_mixer` wrapper for sound effects and music.

```cpp
AudioManager() = default;
~AudioManager();  // calls Destroy()

bool Init();
void Destroy();

bool LoadSound(const std::string& name, const std::string& path);
bool LoadMusic(const std::string& name, const std::string& path);

void PlaySound(const std::string& name, int loops = 0);
void PlayMusic(const std::string& name, int loops = -1);

void StopMusic();
void PauseMusic();
void ResumeMusic();

void SetSoundVolume(int volume);   // 0–128 (SDL_mixer's MIX_MAX_VOLUME range)
void SetMusicVolume(int volume);   // 0–128
```

**Notes**
- Sounds/music are keyed by a `name` you choose at load time, not by path — lets you reference `"jump"` instead of the file path everywhere.
- `PlayMusic` defaults to `loops = -1` (infinite loop). `PlaySound` defaults to `loops = 0` (play once).
- Initialized internally with 32 mixing channels, 44.1kHz stereo.

---

## TileMap

Loads [Tiled](https://www.mapeditor.org/) `.json` map exports and `.tsx` tileset XML for per-tile metadata (solid flags, animated tiles).

```cpp
bool Load(const std::string& path);                          // Tiled .json map
bool LoadTileset(Renderer& renderer, const char* path);       // tileset image
bool LoadTilesetProperties(const std::string& path);          // .tsx (solid/animated flags)

void Update(float dt);     // advances animated tile frames
void Draw(Renderer& renderer);

bool Solid(int tile) const;
int GetTile(int tileX, int tileY) const;

int GetTileWidth() const;
int GetTileHeight() const;
int GetMapWidth() const;
int GetMapHeight() const;

const std::vector<MapObject>& GetObjects() const;
```

```cpp
// MapObject — from Tiled object layers
struct MapObject {
    std::string name;
    std::string type;
    float x, y, width, height;
    std::unordered_map<std::string, float> properties;  // numeric custom properties only
};
```

**Notes**
- `Load()` reads Tiled's JSON export: `tilelayer` entries populate the tile grid, `objectgroup` entries populate `GetObjects()` (spawn points, triggers, etc). Tiled's flip/rotation bit flags on GIDs are stripped automatically.
- `LoadTilesetProperties()` parses the companion `.tsx` file (raw XML string search, not a full XML parser) to pick up per-tile `Solid` custom properties and `<animation>` frame data.
- ⚠️ `MapObject::properties` only captures **numeric** custom properties from Tiled (`is_number()` check) — string/bool custom properties in Tiled are currently silently skipped.
- Depends on `nlohmann/json` (`External/json.hpp`) for the `.json` parsing.

---

## Known Gaps / Rough Edges

Being upfront about what's incomplete so you're not debugging your own game logic when it's actually this:

- `Entity::sprite` is a `Texture`, not the more capable `Sprite` class — animated entities need a custom draw path for now.
- `Animation` only supports single-row (horizontal) spritesheets.
- `SceneManager::ChangeScene` doesn't call `Unload()` on the outgoing scene.
- `TileMap::MapObject::properties` drops non-numeric Tiled custom properties.
- No built-in collision **resolution** (only detection via `Collider::Intersects`) — you write your own response logic.
- `Collider::Destroy()` just sets a flag; nothing acts on it automatically.

PRs welcome on any of these — see [CONTRIBUTING](../README.md#-contributing).
