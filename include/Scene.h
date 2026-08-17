#pragma once


class Renderer;

class Scene{

public:

    virtual ~Scene() = default;

    virtual void Load() = 0;
    virtual void Update(float dt) = 0;

    virtual void Draw(Renderer& renderer) = 0;

    virtual void Unload() = 0;

};
