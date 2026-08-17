#pragma once

#include "Texture.h"
#include "Renderer.h"
#include "Animation.h"

class Sprite{

public:

    void SetTexture(Texture& texture);

    void SetPosition(float x, float y);

    void SetSize(float width, float height);

    void SetRotation(double angle);

    void SetAnimation(Animation& animation);

    void SetFlip(SDL_RendererFlip flip);

    float GetX() const{
        return x;
    }

    float GetY() const{
        return y;
    }

    float GetWidth() const{
        return width;
    }

    float GetHeight() const{
        return height;
    }

    double GetRotation() const{
        return rotation;
    }

    void Draw(Renderer& renderer);


    void FlipHorizontal();
    void FlipVertical();
    void ResetFlip();


    Animation* GetAnimation() const{
        return animation;
    }


private:

    Texture* texture = nullptr;
    Animation* animation = nullptr;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    float x = 0.0f;
    float y = 0.0f;

    float width = 0.0f;
    float height = 0.0f;

    double rotation = 0.0;


};
