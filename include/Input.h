#pragma once
#include <SDL2/SDL.h>
#include <SDL_keyboard.h>
#include "Key.h"


using namespace std;


class Input{


public:

    Input(){
        currKey = SDL_GetKeyboardState(nullptr);
    }

    void Update();

    bool isKeyHeld(Key key);
    bool isKeyPressed(Key key);

private:

    const Uint8* currKey = nullptr;
    Uint8 prevKey[SDL_NUM_SCANCODES] = {0};


};

