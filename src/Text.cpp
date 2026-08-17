#include "Text.h"
#include <iostream>
using namespace std;

bool Text::Load(Renderer& renderer, const char* fontPath, int fontSize){
    font = TTF_OpenFont(fontPath, fontSize);

    if(!font){
        cout << "Failed to load font: " << TTF_GetError() << endl;
        return false;
    }
    return true;
}

bool Text::Draw(Renderer& renderer, const char* text, int x, int y){
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if(!surface) return false;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer.GetSDLRenderer(), surface);
    int w = surface->w, h = surface->h;
    SDL_FreeSurface(surface);
    if(!tex) return false;


    SDL_Rect dest = {

        renderer.TransformX(x),
        renderer.TransformY(y),
        w, 
        h

    };


    SDL_RenderCopy(renderer.GetSDLRenderer(), tex, nullptr, &dest);
    SDL_DestroyTexture(tex);
    return true;
}


void Text::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){

    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;

}


void Text::Destroy(){
    if(font){
        TTF_CloseFont(font);
        font = nullptr;
    }
}
