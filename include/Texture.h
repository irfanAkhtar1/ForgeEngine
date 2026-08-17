#pragma once
#include <SDL2/SDL.h>
#include "Renderer.h"

class Texture{
public:

    bool Load(Renderer& renderer, const char* path);

    bool Draw(Renderer& renderer, float x, float y, float width, float height, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE);


    bool Draw(
    
        Renderer& renderer,
        float x,
        float y,
        float width,
        float height,


        int srcX,
        int srcY,
        int srcW,
        int srcH,

        double angle = 0.0,
        SDL_RendererFlip flip = SDL_FLIP_NONE


    );

    void Destroy();
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }



private:
    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;

};
