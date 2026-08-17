#pragma once

#include "Entity.h"
#include "AudioManager.h"
#include  "Player.h"

class Coin : public Entity
{
public:

    bool Load(Renderer& renderer, const char* path);

    void Update(float dt) override;

    void Draw(Renderer& renderer) override;

    bool CheckCollision(Player& player);

};
