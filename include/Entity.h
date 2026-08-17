#pragma once

#include "Texture.h"
#include "Collider.h"
#include "PhysicsBody.h"


class Renderer;

class Entity{

public:

    virtual ~Entity() = default;

    virtual void Update(float dt);
    virtual void Draw(Renderer& renderer);

    Texture sprite;

    Collider collider;

    Collider& GetCollider(){

        return collider;
    }

    const Collider& GetCollider() const{
        return collider;
    }

    PhysicsBody body;

    void SetPosition(float x, float y);

protected:

    int width = 16;
    int height = 16;



};

