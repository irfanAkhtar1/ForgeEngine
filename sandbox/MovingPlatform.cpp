#include "headers/MovingPlatform.h"
#include "Renderer.h"
#include <iostream>

bool MovingPlatform::Load(Renderer& renderer, const char* path)
{
    if(!sprite.Load(renderer, path)){
        std::cout << "Platform texture failed to load: " << path << std::endl;
    }else{
        std::cout << "PLATFORM TEXTURE OK: " << path << std::endl;
    }

    width = 30;
    height = 7;

    collider.SetSize(width, height);
    body.SetGravity(0.0f);

    return true;
}

void MovingPlatform::SetRange(float moveX, float moveY){
    startX = collider.GetX();
    startY = collider.GetY();

    endX = startX + moveX;
    endY = startY + moveY;
}

void MovingPlatform::SetSpeed(float s)
{
    speed = s;
}


void MovingPlatform::Update(float dt)
{
    float prevX = collider.GetX();
    float prevY = collider.GetY();

    float vx = 0.0f;
    float vy = 0.0f;

    if(movingRight)
    {
        if(startX != endX)
            vx = speed * ((endX > startX) ? 1.0f : -1.0f);

        if(startY != endY)
            vy = speed * ((endY > startY) ? 1.0f : -1.0f);
    }
    else
    {
        if(startX != endX)
            vx = speed * ((startX > endX) ? 1.0f : -1.0f);

        if(startY != endY)
            vy = speed * ((startY > endY) ? 1.0f : -1.0f);
    }

    body.SetVelocityX(vx);
    body.SetVelocityY(vy);

    Entity::Update(dt);

    if(movingRight)
    {
        bool reachedX =
            (vx >= 0 && collider.GetX() >= endX) ||
            (vx <= 0 && collider.GetX() <= endX);

        bool reachedY =
            (vy >= 0 && collider.GetY() >= endY) ||
            (vy <= 0 && collider.GetY() <= endY);

        if((startX == endX || reachedX) &&
           (startY == endY || reachedY))
        {
            movingRight = false;
        }
    }
    else
    {
        bool reachedX =
            (vx >= 0 && collider.GetX() >= startX) ||
            (vx <= 0 && collider.GetX() <= startX);

        bool reachedY =
            (vy >= 0 && collider.GetY() >= startY) ||
            (vy <= 0 && collider.GetY() <= startY);

        if((startX == endX || reachedX) &&
           (startY == endY || reachedY))
        {
            movingRight = true;
        }
    }

    deltaX = collider.GetX() - prevX;
    deltaY = collider.GetY() - prevY;
}

void MovingPlatform::Draw(Renderer& renderer)
{
    Entity::Draw(renderer);

    // Debug collider
    // renderer.DrawRect(
    //     collider.GetX(),
    //     collider.GetY(),
    //     collider.GetWidth(),
    //     collider.GetHeight(),
    //     0, 255, 0
    // );
}
