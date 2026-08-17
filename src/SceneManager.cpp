#include "SceneManager.h"

#include "Renderer.h"

SceneManager::~SceneManager(){

    delete currentScene;
}

void SceneManager::ChangeScene(Scene* newScene){
    delete currentScene;

    currentScene = newScene;

    if(currentScene)
        currentScene->Load();
}

void SceneManager::Update(float dt)
{
    if(currentScene)
        currentScene->Update(dt);
}

void SceneManager::Draw(Renderer& renderer)
{
    if(currentScene)
        currentScene->Draw(renderer);
}
