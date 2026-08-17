#include "Application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

using namespace std;

bool Application::Init(const char* title){

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        cout << "SDL could not initialize!! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    if(TTF_Init() < 0){
        cout << "TTF could not initialize: " << TTF_GetError() << endl;
        return false;
    }

    audio.Init();

    if(viewportW <= 0)
        viewportW = 1280;

    if(viewportH <= 0)
        viewportH = 720;

    if(!window.Create(title, viewportW, viewportH))
        return false;

    if(!renderer.Create(window.GetSDLWindow()))
        return false;

    renderer.SetViewportSize(viewportW, viewportH);
    renderer.SetViewSize(viewW, viewH);
    renderer.SetWorldSize(worldW, worldH);

    renderer.SetColor(100,149,237,255);

    lastCounter = SDL_GetPerformanceCounter();

    isRunning = true;

    return true;


}

void Application::SetColor(int r, int g, int b, int a){

    renderer.SetColor(r, g, b, a);
}

void Application::Run(function<void(Renderer&)> drawCallBack){

    SDL_Event event;

    while(isRunning){
        

        input.Update();

        while(SDL_PollEvent(&event)){

            if(event.type == SDL_QUIT)
                isRunning = false;
        }

        

        Uint64 currCounter = SDL_GetPerformanceCounter();

        deltaTime =
            (currCounter - lastCounter) /
            (float)SDL_GetPerformanceFrequency();

        lastCounter = currCounter;

        renderer.Clear();

        drawCallBack(renderer);

        SDL_RenderPresent(renderer.GetSDLRenderer());

    }
}

void Application::ShutDown(){

    renderer.Destroy();

    window.Destroy();

    audio.Destroy();

    TTF_Quit();

    SDL_Quit();


}

void Application::SetWorldSize(int width, int height){

    worldW = width;
    worldH = height;

    renderer.SetWorldSize(width, height);
}

void Application::SetViewSize(int width, int height){

    viewW = width;
    viewH = height;

    renderer.SetViewSize(width, height);
}

void Application::SetViewportSize(int width, int height){

    viewportW = width;
    viewportH = height;

    renderer.SetViewportSize(width, height);
}
