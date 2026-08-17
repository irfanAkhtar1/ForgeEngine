#pragma once

#include <SDL2/SDL.h>
#include <SDL_render.h>

#include "Camera.h"

class Renderer{

public:

    bool Create(SDL_Window* window);

    void Destroy();

    void SetCamera(Camera* cam);

    Camera* GetCamera() const{
        return camera;
    }

    SDL_Renderer* GetSDLRenderer() const{
        return renderer;
    }

    void SetColor(int r, int g, int b, int a = 255);

    void Clear();

    void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a = 255);

    int TransformX(float x) const;

    int TransformY(float y) const;

    void SetWorldSize(int width, int height);

    void SetViewSize(int width, int height);

    void SetViewportSize(int width, int height);

private:

    SDL_Renderer* renderer = nullptr;

    Camera* camera = nullptr;

    Uint8 clearR = 0;
    Uint8 clearG = 0;
    Uint8 clearB = 0;
    Uint8 clearA = 255;

    int worldW = 0;
    int worldH = 0;

    int viewW = 0;
    int viewH = 0;

    int viewportW = 0;
    int viewportH = 0;

};
