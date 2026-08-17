#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

bool Texture::Load(Renderer& renderer, const char* path){

    texture = IMG_LoadTexture(renderer.GetSDLRenderer(), path);

    if(!texture){
        cout << "Failed to load image: " << IMG_GetError() << endl;
        return false;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    return true;
}

bool Texture::Draw(Renderer& renderer, float x, float y, float width, float height, double angle, SDL_RendererFlip flip){

    SDL_Rect dest = {

        renderer.TransformX(x),
        renderer.TransformY(y),
        (int)width,
        (int)height

    };

    return SDL_RenderCopyEx(
        renderer.GetSDLRenderer(),
        texture,
        nullptr,
        &dest,
        angle,
        nullptr,
        flip
    ) == 0;
}

bool Texture::Draw(
    Renderer& renderer,
    float x,
    float y,
    float width,
    float height,
    int srcX,
    int srcY,
    int srcW,
    int srcH,
    double angle,
    SDL_RendererFlip flip
){

    SDL_Rect src = {

        srcX,
        srcY,
        srcW,
        srcH

    };

    SDL_Rect dest = {

        renderer.TransformX(x),
        renderer.TransformY(y),
        (int)width,
        (int)height

    };

    return SDL_RenderCopyEx(
        renderer.GetSDLRenderer(),
        texture,
        &src,
        &dest,
        angle,
        nullptr,
        flip
    ) == 0;
}

void Texture::Destroy(){

    if(texture){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

}
