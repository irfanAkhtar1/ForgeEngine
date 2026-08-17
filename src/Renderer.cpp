#include "Renderer.h"

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

bool Renderer::Create(SDL_Window* window){

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if(!renderer){
        cout << "Failed to create renderer: " << SDL_GetError() << endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    return true;
}

void Renderer::SetCamera(Camera* cam){

    camera = cam;
}

int Renderer::TransformX(float x) const{

    if(camera)
        return (int)(x - camera->GetX());

    return (int)x;
}

int Renderer::TransformY(float y) const{

    if(camera)
        return (int)(y - camera->GetY());

    return (int)y;
}

void Renderer::SetColor(int r, int g, int b, int a){

    clearR = r;
    clearG = g;
    clearB = b;
    clearA = a;
}

void Renderer::Clear(){

    SDL_SetRenderDrawColor(renderer, clearR, clearG, clearB, clearA);
    SDL_RenderClear(renderer);
}

void Renderer::DrawRect(int x, int y, int w, int h, int r, int g, int b, int a){

    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    SDL_Rect rect = {
        TransformX(x),
        TransformY(y),
        w,
        h
    };

    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::SetWorldSize(int width, int height){

    worldW = width;
    worldH = height;

    if(camera)
        camera->SetWorldSize(width, height);
}

void Renderer::SetViewSize(int width, int height){

    viewW = width;
    viewH = height;

    if(camera)
        camera->SetViewSize(width, height);

    if(renderer)
        SDL_RenderSetLogicalSize(renderer, viewW, viewH);
}

void Renderer::SetViewportSize(int width, int height){

    viewportW = width;
    viewportH = height;
}

void Renderer::Destroy(){

    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
}
