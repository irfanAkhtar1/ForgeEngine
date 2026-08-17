#include "Window.h"

#include <SDL2/SDL.h>

#include <iostream>

using namespace std;

bool Window::Create(const char* title, int width, int height){

    this->width = width;
    this->height = height;

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );

    if(!window){
        cout << "Window failed to create: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void Window::Resize(int width, int height){

    this->width = width;
    this->height = height;

    if(window)
        SDL_SetWindowSize(window, width, height);
}

void Window::Destroy(){

    if(window){
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}
