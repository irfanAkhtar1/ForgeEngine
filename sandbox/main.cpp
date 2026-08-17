#include "Application.h"
#include "SceneManager.h"
#include "headers/GameScene.h"
#include "headers/GameOverScene.h"

int main(int argc, char* argv[])
{
    Application game;

    game.SetWorldSize(1000, 1000);
    game.SetViewSize(640, 320);
    game.SetViewportSize(1280, 640);

    game.Init("Forge Engine");
    game.SetColor(0, 0, 0);

    SceneManager scenes;

    scenes.ChangeScene(new GameScene(game));

    float timer = 0.0f;
    bool changed = false;

    game.Run([&](Renderer& renderer)
    {
        float dt = game.GetDeltaTime();

        timer += dt;

        if(timer >= 100.0f && !changed)
        {
            changed = true;
            scenes.ChangeScene(new GameOverScene(game));
        }

        scenes.Update(dt);
        scenes.Draw(renderer);
    });

    game.ShutDown();

    return 0;
}
