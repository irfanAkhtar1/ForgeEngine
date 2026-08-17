#pragma once

#include <SDL2/SDL.h>

class Window{

public:

    bool Create(const char* title, int width, int height);

    void Destroy();

    void Resize(int width, int height);

    SDL_Window* GetSDLWindow() const{
        return window;
    }

    int GetWidth() const{
        return width;
    }

    int GetHeight() const{
        return height;
    }

private:

    SDL_Window* window = nullptr;

    int width = 0;
    int height = 0;

};
