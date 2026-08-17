#include "AssetManager.h"
#include <stdexcept>
#include <utility>

using namespace std;

Texture& AssetManager::LoadTexture(Renderer& renderer, const string& path){

    auto it = textures.find(path);

    if(it != textures.end()){
        return *it->second;
    }

    auto texture = make_unique<Texture>();

    if(!texture->Load(renderer, path.c_str())){
        throw runtime_error("AssetManager: Failed to load texture: " + path);
    }

    textures[path] = std::move(texture);

    return *textures[path];

}

Texture& AssetManager::GetTexture(const string& path){

    auto it = textures.find(path);

    if(it == textures.end()){
        throw runtime_error("Texture not loaded: " + path);
    }

    return *it->second;

}

Text& AssetManager::LoadFont(Renderer& renderer, const string& path, int size){

    string key = path + ":" + to_string(size);

    auto it = fonts.find(key);

    if(it != fonts.end()){
        return *it->second;
    }

    auto font = make_unique<Text>();

    if(!font->Load(renderer, path.c_str(), size)){
        throw runtime_error("AssetManager: Failed to load font: " + path);
    }

    fonts[key] = std::move(font);

    return *fonts[key];

}

Text& AssetManager::GetFont(const string& path, int size){

    string key = path + ":" + to_string(size);

    auto it = fonts.find(key);

    if(it == fonts.end()){
        throw runtime_error("Font not loaded: " + key);
    }

    return *it->second;

}

void AssetManager::Destroy(){

    for(auto& texture : textures){
        texture.second->Destroy();
    }

    textures.clear();

    for(auto& font : fonts){
        font.second->Destroy();
    }

    fonts.clear();

}
