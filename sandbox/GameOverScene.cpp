#include "headers/GameOverScene.h"

GameOverScene::GameOverScene(Application& app)
    : game(app)
{
}

void GameOverScene::Load()
{
    text = &assets.LoadFont(
        game.GetRenderer(),
        "arial.ttf",
        48
    );
}

void GameOverScene::Update(float dt)
{
}

void GameOverScene::Draw(Renderer& renderer)
{
    text->Draw(renderer,
               "GAME OVER",
               300,
               150);
}

void GameOverScene::Unload()
{
    assets.Destroy();
}
