#pragma once

#include "Scene.h"
#include "Application.h"
#include "AssetManager.h"

class GameOverScene : public Scene
{
public:
    GameOverScene(Application& app);

    void Load() override;
    void Update(float dt) override;
    void Draw(Renderer& renderer) override;
    void Unload() override;

private:
    Application& game;
    AssetManager assets;

    Text* text = nullptr;
};
