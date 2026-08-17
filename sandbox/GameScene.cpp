#include "headers/GameScene.h"

#include "Application.h"
#include "Renderer.h"

#include <cmath>

GameScene::GameScene(Application& app)
    : game(app),
      camera(640, 320)
{
}

void GameScene::Load()
{
    //--------------------------------------------------
    // Camera
    //--------------------------------------------------

    camera.SetWorldSize(1000, 1000);
    game.GetRenderer().SetCamera(&camera);

    //--------------------------------------------------
    // Player
    //--------------------------------------------------

    player.Load(game.GetRenderer(), assets);
    player.SetAttackHitboxFrames(3, 4);

    //--------------------------------------------------
    // TileMap
    //--------------------------------------------------

    map.Load("assets/maps/Level1.tmj");
    map.LoadTilesetProperties("./assets/tiles/TileSet.tsx");
    map.LoadTileset(game.GetRenderer(), "assets/tiles/TileSet.png");

    //--------------------------------------------------
    // Coins
    //--------------------------------------------------

    for (const auto& obj : map.GetObjects())
    {
        if (obj.type == "Coin")
        {
            Coin coin;

            coin.Load(
                game.GetRenderer(),
                "./assets/Images/Coin/coin.jpg"
            );

            coin.SetPosition(obj.x, obj.y);

            coins.push_back(std::move(coin));
        }
    }

    //--------------------------------------------------
    // Moving Platforms
    //--------------------------------------------------

    for (const auto& obj : map.GetObjects())
    {
        if (obj.type == "MovingPlatform")
        {
            MovingPlatform platform;

            platform.Load(
                game.GetRenderer(),
                "./assets/Images/platform/platform.png"
            );

            platform.SetPosition(obj.x, obj.y);

            float moveX = 0.0f;
            float moveY = 0.0f;
            float speed = 80.0f;

            if (obj.properties.count("moveX"))
                moveX = obj.properties.at("moveX");

            if (obj.properties.count("moveY"))
                moveY = obj.properties.at("moveY");

            if (obj.properties.count("speed"))
                speed = obj.properties.at("speed");

            platform.SetRange(moveX, moveY);
            platform.SetSpeed(speed);

            platforms.push_back(std::move(platform));
        }
    }

    //--------------------------------------------------
    // Audio
    //--------------------------------------------------

    game.GetAudio().LoadMusic(
        "Music",
        "./assets/Audio/Music.wav"
    );

    game.GetAudio().PlayMusic("Music", -1);

    game.GetAudio().LoadSound(
        "Coin",
        "./assets/Audio/Coin.mp3"
    );

    //--------------------------------------------------
    // Font
    //--------------------------------------------------

    label = &assets.LoadFont(
        game.GetRenderer(),
        "arial.ttf",
        24
    );
}

void GameScene::Update(float dt)
{
    map.Update(dt);

    //--------------------------------------------------
    // Platforms
    //--------------------------------------------------

    for (auto& platform : platforms)
        platform.Update(dt);

    //--------------------------------------------------
    // Player
    //--------------------------------------------------

    player.HandleInput(game.GetInput(), dt);
    player.Update(dt);

    //--------------------------------------------------
    // Ground List
    //--------------------------------------------------

    grounds.clear();

    for (int y = 0; y < map.GetMapHeight(); y++)
    {
        for (int x = 0; x < map.GetMapWidth(); x++)
        {
            int tile = map.GetTile(x, y);

            if (!map.Solid(tile))
                continue;

            grounds.emplace_back(
                x * map.GetTileWidth(),
                y * map.GetTileHeight(),
                map.GetTileWidth(),
                map.GetTileHeight()
            );
        }
    }

    for (auto& platform : platforms)
        grounds.push_back(platform.GetCollider());

    //--------------------------------------------------
    // Ride Moving Platforms
    //--------------------------------------------------

    for (auto& platform : platforms)
    {
        Collider& playerCol = player.GetCollider();

        float playerBottom =
            playerCol.GetY() + playerCol.GetHeight();

        float platformTop =
            platform.GetCollider().GetY();

        bool onTop =
            std::fabs(playerBottom - platformTop) < 8.0f &&
            playerCol.GetX() + playerCol.GetWidth() >
                platform.GetCollider().GetX() &&
            playerCol.GetX() <
                platform.GetCollider().GetX() +
                platform.GetCollider().GetWidth();

        if (onTop && player.IsOnGround())
        {
            playerCol.SetPosition(
                playerCol.GetX() + platform.GetDeltaX(),
                playerCol.GetY() + platform.GetDeltaY()
            );
        }
    }

    //--------------------------------------------------
    // Resolve Player Collision
    //--------------------------------------------------

    player.ResolveCollisions(grounds, dt);

    //--------------------------------------------------
    // Coins
    //--------------------------------------------------

    for (auto& coin : coins)
    {
        coin.Update(dt);

        if (coin.CheckCollision(player))
            game.GetAudio().PlaySound("Coin");
    }

    //--------------------------------------------------
    // Camera
    //--------------------------------------------------

    camera.Follow(
        player.GetX() + 48.0f,
        player.GetY() + 30.5f,
        0.08f
    );
}

void GameScene::Draw(Renderer& renderer)
{
    //--------------------------------------------------
    // Debug Ground
    //--------------------------------------------------

    for (auto& ground : grounds)
    {
        renderer.DrawRect(
            ground.GetX(),
            ground.GetY(),
            ground.GetWidth(),
            ground.GetHeight(),
            90, 190, 90
        );
    }

    //--------------------------------------------------
    // World
    //--------------------------------------------------

    map.Draw(renderer);

    for (auto& coin : coins)
        coin.Draw(renderer);

    for (auto& platform : platforms)
        platform.Draw(renderer);

    player.Draw(renderer);

    //--------------------------------------------------
    // UI
    //--------------------------------------------------

    label->Draw(
        renderer,
        "Forge Engine",
        50,
        50
    );
}

void GameScene::Unload()
{
    assets.Destroy();
}

