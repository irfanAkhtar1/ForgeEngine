#pragma once

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "AudioManager.h"

#include <functional>

class Application{

public:

    Input& GetInput(){
        return input;
    }

    bool Init(const char* title);

    void SetWorldSize(int width, int height);

    void SetViewSize(int width, int height);

    void SetViewportSize(int width, int height);

    void Run(std::function<void(Renderer&)> drawCallback);

    void SetColor(int r, int g, int b, int a = 255);

    float GetDeltaTime() const{
        return deltaTime;
    }

    void ShutDown();

    Renderer& GetRenderer(){
        return renderer;
    }

    SDL_Window* GetSDLWindow() const{
        return window.GetSDLWindow();
    }

    int GetWorldWidth() const{
        return worldW;
    }

    int GetWorldHeight() const{
        return worldH;
    }

    int GetViewWidth() const{
        return viewW;
    }

    int GetViewHeight() const{
        return viewH;
    }

    int GetViewportWidth() const{
        return viewportW;
    }

    int GetViewportHeight() const{
        return viewportH;
    }


    AudioManager& GetAudio(){
        return audio;
    }



private:

    Window window;
    Renderer renderer;
    Input input;

    bool isRunning = false;

    float deltaTime = 0.0f;
    Uint64 lastCounter = 0;

    int worldW = 320;
    int worldH = 180;

    int viewW = 320;
    int viewH = 180;

    int viewportW = 1280;
    int viewportH = 720;

    AudioManager audio;

};
