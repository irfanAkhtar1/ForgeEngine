#pragma once

#include "Entity.h"

class MovingPlatform : public Entity
{
public:

    bool Load(Renderer& renderer, const char* path);

    void Update(float dt) override;

    void Draw(Renderer& renderer) override;

    void SetRange(float left, float right);

    void SetSpeed(float s);

    float GetDeltaX() const { return deltaX; }
    float GetDeltaY() const { return deltaY; }

    void SetMovement(float moveX, float moveY);

private:

    float startX = 0.0f;
    float startY = 0.0f;

    float endX = 0.0f;
    float endY = 0.0f;

    float speed = 100.0f;

    bool movingRight = true;

    float deltaX = 0.0f;
    float deltaY = 0.0f;
};
