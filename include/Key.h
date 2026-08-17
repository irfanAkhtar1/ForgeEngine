#pragma once
#include <SDL2/SDL.h>

enum class Key{
    // Letters
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    // Numbers (top row)
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    // Arrows
    Up, Down, Left, Right,
    // Common controls
    Space, Enter, Escape, Tab, Backspace, LShift, RShift, LCtrl, RCtrl, LAlt, RAlt,
    // Function keys
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
};

inline SDL_Scancode ToSDLScancode(Key key){
    switch(key){
        case Key::A: return SDL_SCANCODE_A;
        case Key::B: return SDL_SCANCODE_B;
        case Key::C: return SDL_SCANCODE_C;
        case Key::D: return SDL_SCANCODE_D;
        case Key::E: return SDL_SCANCODE_E;
        case Key::F: return SDL_SCANCODE_F;
        case Key::G: return SDL_SCANCODE_G;
        case Key::H: return SDL_SCANCODE_H;
        case Key::I: return SDL_SCANCODE_I;
        case Key::J: return SDL_SCANCODE_J;
        case Key::K: return SDL_SCANCODE_K;
        case Key::L: return SDL_SCANCODE_L;
        case Key::M: return SDL_SCANCODE_M;
        case Key::N: return SDL_SCANCODE_N;
        case Key::O: return SDL_SCANCODE_O;
        case Key::P: return SDL_SCANCODE_P;
        case Key::Q: return SDL_SCANCODE_Q;
        case Key::R: return SDL_SCANCODE_R;
        case Key::S: return SDL_SCANCODE_S;
        case Key::T: return SDL_SCANCODE_T;
        case Key::U: return SDL_SCANCODE_U;
        case Key::V: return SDL_SCANCODE_V;
        case Key::W: return SDL_SCANCODE_W;
        case Key::X: return SDL_SCANCODE_X;
        case Key::Y: return SDL_SCANCODE_Y;
        case Key::Z: return SDL_SCANCODE_Z;

        case Key::Num0: return SDL_SCANCODE_0;
        case Key::Num1: return SDL_SCANCODE_1;
        case Key::Num2: return SDL_SCANCODE_2;
        case Key::Num3: return SDL_SCANCODE_3;
        case Key::Num4: return SDL_SCANCODE_4;
        case Key::Num5: return SDL_SCANCODE_5;
        case Key::Num6: return SDL_SCANCODE_6;
        case Key::Num7: return SDL_SCANCODE_7;
        case Key::Num8: return SDL_SCANCODE_8;
        case Key::Num9: return SDL_SCANCODE_9;

        case Key::Up: return SDL_SCANCODE_UP;
        case Key::Down: return SDL_SCANCODE_DOWN;
        case Key::Left: return SDL_SCANCODE_LEFT;
        case Key::Right: return SDL_SCANCODE_RIGHT;

        case Key::Space: return SDL_SCANCODE_SPACE;
        case Key::Enter: return SDL_SCANCODE_RETURN;
        case Key::Escape: return SDL_SCANCODE_ESCAPE;
        case Key::Tab: return SDL_SCANCODE_TAB;
        case Key::Backspace: return SDL_SCANCODE_BACKSPACE;
        case Key::LShift: return SDL_SCANCODE_LSHIFT;
        case Key::RShift: return SDL_SCANCODE_RSHIFT;
        case Key::LCtrl: return SDL_SCANCODE_LCTRL;
        case Key::RCtrl: return SDL_SCANCODE_RCTRL;
        case Key::LAlt: return SDL_SCANCODE_LALT;
        case Key::RAlt: return SDL_SCANCODE_RALT;

        case Key::F1: return SDL_SCANCODE_F1;
        case Key::F2: return SDL_SCANCODE_F2;
        case Key::F3: return SDL_SCANCODE_F3;
        case Key::F4: return SDL_SCANCODE_F4;
        case Key::F5: return SDL_SCANCODE_F5;
        case Key::F6: return SDL_SCANCODE_F6;
        case Key::F7: return SDL_SCANCODE_F7;
        case Key::F8: return SDL_SCANCODE_F8;
        case Key::F9: return SDL_SCANCODE_F9;
        case Key::F10: return SDL_SCANCODE_F10;
        case Key::F11: return SDL_SCANCODE_F11;
        case Key::F12: return SDL_SCANCODE_F12;
    }
    return SDL_SCANCODE_UNKNOWN;
}
