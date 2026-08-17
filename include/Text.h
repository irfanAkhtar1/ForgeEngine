#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Renderer.h"

class Text{
public:

    bool Load(Renderer& renderer, const char* fontPath, int fontSize);

    bool Draw(Renderer& renderer, const char* text, int x, int y);

    void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

    void Destroy();


private:

    TTF_Font* font = nullptr;

    SDL_Color color = {255, 255, 255, 255};
};
