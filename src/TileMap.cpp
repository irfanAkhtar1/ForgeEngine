#include "TileMap.h"
#include "Renderer.h"
#include "Texture.h"

#include <fstream>
#include <iostream>

#include <../External/json.hpp>

using json = nlohmann::json;
using namespace std;

bool TileMap::Load(const string& path){

    tiles.clear();
    objects.clear();

    ifstream file(path);

    if(!file.is_open()){
        cout << "Failed to open map: " << path << endl;
        return false;
    }

    json data;

    try{
        file >> data;
    } catch(const std::exception& e){
        cout << "Failed to parse map JSON: " << e.what() << endl;
        return false;
    }

    mapWidth   = data.value("width", 0);
    mapHeight  = data.value("height", 0);
    tileWidth  = data.value("tilewidth", 0);
    tileHeight = data.value("tileheight", 0);

    if(!data.contains("layers"))
        return false;

    for(const auto& layer : data["layers"]){

        string layerType = layer.value("type", "");

        //--------------------------------------------------
        // Tile layer -> fill `tiles`
        //--------------------------------------------------
        if(layerType == "tilelayer" && layer.contains("data")){

            for(auto gid : layer["data"]){
                unsigned int value = gid.get<unsigned int>();
                value &= 0x1FFFFFFF; // strip Tiled flip/rotation flags
                tiles.push_back((int)value);
            }
        }

        //--------------------------------------------------
        // Object layer -> fill `objects`
        //--------------------------------------------------
        if(layerType == "objectgroup" && layer.contains("objects")){

            for(const auto& obj : layer["objects"]){

                MapObject mo;

                mo.name   = obj.value("name", "");
                mo.type   = obj.value("type", obj.value("class", ""));
                mo.x      = obj.value("x", 0.0f);
                mo.y      = obj.value("y", 0.0f);
                mo.width  = obj.value("width", 0.0f);
                mo.height = obj.value("height", 0.0f);

                if(obj.contains("properties")){
                    for(const auto& prop : obj["properties"]){

                        std::string propName = prop.value("name", "");

                        if(prop.contains("value") && prop["value"].is_number()){
                            mo.properties[propName] = prop["value"].get<float>();
                        }

                    }
                }
            
                objects.push_back(mo);
            }
        }
    }

    cout << "====== TileMap Loaded ======" << endl;
    cout << "Map Width   : " << mapWidth << endl;
    cout << "Map Height  : " << mapHeight << endl;
    cout << "Tile Width  : " << tileWidth << endl;
    cout << "Tile Height : " << tileHeight << endl;
    cout << "Tiles Loaded: " << tiles.size() << endl;
    cout << "Objects     : " << objects.size() << endl;
    cout << "============================" << endl;

    return true;
}

int TileMap::GetTile(int tileX, int tileY) const{

    if(tileX < 0 || tileX >= mapWidth)
        return 0;

    if(tileY < 0 || tileY >= mapHeight)
        return 0;

    return tiles[tileY * mapWidth + tileX];
}

bool TileMap::LoadTilesetProperties(const std::string& path)
{
    // .tsx is XML, not JSON — stays as manual parsing.

    ifstream file(path);

    if(!file.is_open())
    {
        cout << "Failed to open tileset: " << path << endl;
        return false;
    }

    string text(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    solidTiles.assign(257, false);

    size_t pos = 0;

    while(true)
    {
        pos = text.find("<tile id=\"", pos);

        if(pos == string::npos)
            break;

        pos += 10;

        size_t end = text.find("\"", pos);

        int id = stoi(text.substr(pos, end - pos));

        size_t tileEnd = text.find("</tile>", end);

        string block = text.substr(end, tileEnd - end);

        if(id + 1 >= (int)solidTiles.size())
            solidTiles.resize(id + 2, false);

        size_t propPos = block.find("name=\"Solid\"");

        if(propPos != string::npos)
        {
            size_t valPos = block.find("value=\"", propPos);

            if(valPos != string::npos)
            {
                valPos += 7;

                size_t valEnd = block.find("\"", valPos);

                string val = block.substr(valPos, valEnd - valPos);

                if(val == "true" || val == "1")
                    solidTiles[id + 1] = true;
            }
        }

        size_t animPos = block.find("<animation>");

        if(animPos != string::npos)
        {
            AnimatedTile anim;
            anim.tileID = id + 1;

            size_t framePos = animPos;

            while(true)
            {
                framePos = block.find("<frame", framePos);

                if(framePos == string::npos)
                    break;

                AnimatedFrame frame;

                size_t tileidPos = block.find("tileid=\"", framePos);

                if(tileidPos == string::npos)
                    break;

                tileidPos += 8;

                size_t tileidEnd = block.find("\"", tileidPos);

                frame.tileID =
                    stoi(block.substr(tileidPos, tileidEnd - tileidPos))
                    + 1;

                size_t durPos = block.find("duration=\"", framePos);

                if(durPos == string::npos)
                    break;

                durPos += 10;

                size_t durEnd = block.find("\"", durPos);

                frame.duration =
                    stoi(block.substr(durPos, durEnd - durPos));

                anim.frames.push_back(frame);

                framePos = durEnd;
            }

            if(!anim.frames.empty())
                animatedTiles.push_back(anim);
        }

        pos = tileEnd;
    }

    cout << "====== Tileset Properties Loaded ======" << endl;

    int solidCount = 0;
    for(bool s : solidTiles) if(s) solidCount++;

    cout << "Solid tiles: " << solidCount << endl;
    cout << "Animated tiles: " << animatedTiles.size() << endl;
    cout << "========================================" << endl;

    return true;
}

bool TileMap::Solid(int tile) const
{
    if(tile < 0 || tile >= (int)solidTiles.size())
        return false;

    return solidTiles[tile];
}

void TileMap::Update(float dt)
{
    for(auto& anim : animatedTiles)
    {
        if(anim.frames.empty())
            continue;

        anim.timer += dt;

        if(anim.timer >= anim.frames[anim.currentFrame].duration / 1000.0f)
        {
            anim.timer = 0.0f;
            anim.currentFrame++;

            if(anim.currentFrame >= (int)anim.frames.size())
                anim.currentFrame = 0;
        }
    }
}

int TileMap::GetAnimatedFrame(int tile) const
{
    for(const auto& anim : animatedTiles)
    {
        if(anim.tileID == tile)
            return anim.frames[anim.currentFrame].tileID;
    }

    return tile;
}

bool TileMap::LoadTileset(Renderer& renderer, const char* path)
{
    return tileset.Load(renderer, path);
}

void TileMap::Draw(Renderer& renderer)
{
    if(tileWidth <= 0 || tileHeight <= 0)
        return;

    int tilesPerRow = tileset.GetWidth() / tileWidth;

    if(tilesPerRow <= 0)
        return;

    for(int y = 0; y < mapHeight; y++)
    {
        for(int x = 0; x < mapWidth; x++)
        {
            int index = y * mapWidth + x;

            if(index >= (int)tiles.size())
                continue;

            int tile = GetAnimatedFrame(tiles[index]);

            if(tile == 0)
                continue;

            tile--;

            int srcX = (tile % tilesPerRow) * tileWidth;
            int srcY = (tile / tilesPerRow) * tileHeight;

            tileset.Draw(
                renderer,
                x * tileWidth,
                y * tileHeight,
                tileWidth,
                tileHeight,
                srcX,
                srcY,
                tileWidth,
                tileHeight
            );
        }
    }
}
