#include "Input.h"
#include <cstring>
#include <SDL2/SDL.h>

using namespace std;


void Input::Update(){

    memcpy(prevKey, currKey, SDL_NUM_SCANCODES);
    currKey = SDL_GetKeyboardState(nullptr);

}


bool Input::isKeyHeld(Key key){

    SDL_Scancode scancode = ToSDLScancode(key);

    return currKey[scancode];

}

bool Input::isKeyPressed(Key key){


    SDL_Scancode scancode = ToSDLScancode(key);

    return (currKey[scancode]) && (!prevKey[scancode]);

}
