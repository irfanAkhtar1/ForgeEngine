#include <unordered_map>
#pragma once

#include <vector>
#include <string>

#include "Texture.h"
#include "Collider.h"

class Renderer;

struct AnimatedFrame
{
    int tileID;
    int duration;
};

struct AnimatedTile
{
    int tileID = 0;

    std::vector<AnimatedFrame> frames;

    int currentFrame = 0;
    float timer = 0.0f;
};

struct MapObject
{
    std::string name;
    std::string type;

    float x;
    float y;

    float width;
    float height;

    std::unordered_map<std::string, float> properties;

};

class TileMap
{
public:

    bool Load(const std::string& path);

    bool LoadTileset(Renderer& renderer, const char* path);

    bool LoadTilesetProperties(const std::string& path);

    void Update(float dt);

    void Draw(Renderer& renderer);

    bool Solid(int tile) const;

    int GetTile(int tileX, int tileY) const;

    int GetTileWidth() const{
        return tileWidth;
    }

    int GetTileHeight() const{
        return tileHeight;
    }

    int GetMapWidth() const{
        return mapWidth;
    }

    int GetMapHeight() const{
        return mapHeight;
    }

    const std::vector<MapObject>& GetObjects() const
    {
        return objects;
    }

private:

    int GetAnimatedFrame(int tile) const;

    int mapWidth = 0;
    int mapHeight = 0;

    int tileWidth = 0;
    int tileHeight = 0;

    std::vector<int> tiles;

    std::vector<MapObject> objects;

    Texture tileset;

    std::vector<bool> solidTiles;

    std::vector<AnimatedTile> animatedTiles;
};
