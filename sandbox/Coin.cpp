#include "headers/Coin.h"
#include "PhysicsBody.h"
#include "headers/Player.h"

bool Coin::Load(Renderer& renderer, const char* path){
    if(!sprite.Load(renderer, path))
        return false;

    width = 16;
    height = 16;

    collider.SetSize(width, height);

    body.SetGravity(0.0f);

    return true;
}

void Coin::Update(float dt)
{
    Entity::Update(dt);
}

void Coin::Draw(Renderer& renderer)
{
    if(collider.IsDestroyed())
        return;

    Entity::Draw(renderer);
}

bool Coin::CheckCollision(Player& player)
{
    if(collider.IsDestroyed())
        return false;

    if(collider.Intersects(player.GetCollider()))
    {
        collider.Destroy();
        return true;
    }

    return false;
}
