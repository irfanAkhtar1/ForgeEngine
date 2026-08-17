#pragma once 

#include "Scene.h"

class Renderer;

class SceneManager{

public:

    ~SceneManager();

    void ChangeScene(Scene* newScene);

    void Update(float dt);

    void Draw(Renderer& renderer);

private:

    Scene* currentScene = nullptr;


};
