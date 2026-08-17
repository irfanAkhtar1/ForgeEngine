#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "Texture.h"
#include "Text.h"
#include "Renderer.h"


using namespace std;

class AssetManager{
public:

    Texture& LoadTexture(Renderer& renderer, const string& path);
    Texture& GetTexture(const string& path);

    Text& LoadFont(Renderer& renderer, const string& path, int size);

    Text& GetFont(const string& path, int size);

    void Destroy();

private:

    unordered_map<string,unique_ptr<Texture>> textures;
    unordered_map<string,unique_ptr<Text>> fonts;

};
