#pragma once

#include "Scene.h"

#include "Player.h"
#include "MovingPlatform.h"
#include "Coin.h"

#include "Camera.h"
#include "TileMap.h"
#include "AssetManager.h"

#include <vector>

class Application;
class Renderer;

class GameScene : public Scene
{
public:

    GameScene(Application& app);

    void Load() override;
    void Update(float dt) override;
    void Draw(Renderer& renderer) override;
    void Unload() override;

private:

    Application& game;

    AssetManager assets;

    Camera camera;

    Player player;

    TileMap map;

    std::vector<Coin> coins;

    std::vector<MovingPlatform> platforms;

    std::vector<Collider> grounds;

    Text* label = nullptr;
};
