#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Animation.h"
#include "AssetManager.h"
#include "Input.h"
#include <vector>

class Player : public Entity
{
public:
    void Load(Renderer& renderer, AssetManager& assets);
    void HandleInput(Input& input, float dt);
    void Update(float dt) override;
    void Draw(Renderer& renderer) override;
    void ResolveCollisions(std::vector<Collider>& grounds, float dt);
    void SetAttackHitboxFrames(int startFrame, int endFrame);

    bool IsOnGround() const { return onGround; }
    bool IsAttacking() const { return attacking; }
    bool IsSwordActive() const { return swordActive; }

    Collider& GetSwordHitbox() { return swordHitBox; }

    float GetX() const { return collider.GetX(); }
    float GetY() const { return collider.GetY(); }

private:
    // Temporary.
    // Later this will move into Entity once every entity supports animation.
    Sprite sprite;
    Collider swordHitBox;
    Animation idle, walk, jump, attack;

    float colliderOffsetX = 0.0f;
    float colliderOffsetY = 0.0f;

    float moveSpeed = 250.0f;

    bool moving = false;
    bool onGround = false;
    bool attacking = false;
    bool swordActive = false;
    bool flipped = false;

    int attackHitboxStartFrame = 3;
    int attackHitboxEndFrame = 4;
};
