#pragma once 
#include "Texture.h"
#include <SDL2/SDL.h>



class Animation{

public:

    void SetTexture(Texture& texture);

    void SetFrame(int width, int height);

    void SetFrameCount(int count);

    void SetFPS(float fps);

    void Update(float dt);

    int GetFrameX() const;

    int GetFrameY() const ;

    int GetFrameWidth() const;

    int GetFrameHeight() const;

    Texture* GetTexture() const{

        return texture;

    }

    int GetCurrFrame() const{
        return currFrame;
    }

    void Reset();


private:

    Texture* texture = nullptr;

    int frameWidth = 0;
    int frameHeight = 0;

    int totalFrame = 1;
    int currFrame = 0;

    float fps = 8.0f;
    float timer = 0.0f;

};
