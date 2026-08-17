#include "Entity.h"
#include "Renderer.h"

void Entity::Update(float dt)
{
    body.Update(dt);

    collider.SetPosition(
        collider.GetX() + body.GetVelocityX() * dt,
        collider.GetY() + body.GetVelocityY() * dt
    );
}

void Entity::Draw(Renderer& renderer)
{
    sprite.Draw(
        renderer,
        (int)collider.GetX(),
        (int)collider.GetY(),
        width,
        height
    );
}


void Entity::SetPosition(float x, float y){
    collider.SetPosition(x, y);
}
