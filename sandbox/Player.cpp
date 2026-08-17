#include "headers/Player.h"
#include "Renderer.h"

void Player::Load(Renderer& renderer, AssetManager& assets){

    Texture& idleTex   = assets.LoadTexture(renderer, "./assets/Images/playerSprites/IDLE.png");
    Texture& walkTex   = assets.LoadTexture(renderer, "./assets/Images/playerSprites/WALK.png");
    Texture& jumpTex   = assets.LoadTexture(renderer, "./assets/Images/playerSprites/JUMP.png");
    Texture& attackTex = assets.LoadTexture(renderer, "./assets/Images/playerSprites/ATTACK.png");

    idle.SetTexture(idleTex);
    idle.SetFrame(96, 84);
    idle.SetFrameCount(7);
    idle.SetFPS(8);

    walk.SetTexture(walkTex);
    walk.SetFrame(96, 84);
    walk.SetFrameCount(8);
    walk.SetFPS(12);

    jump.SetTexture(jumpTex);
    jump.SetFrame(96, 61);
    jump.SetFrameCount(5);
    jump.SetFPS(5);

    attack.SetTexture(attackTex);
    attack.SetFrame(96, 84);
    attack.SetFrameCount(6);
    attack.SetFPS(15);

    // collider = the actual physics hitbox, this is the single source of truth for position
    collider.SetPosition(300.0f, 100.0f);
    collider.SetSize(20, 20);

    sprite.SetAnimation(idle);
    sprite.SetSize(96, 61);

    swordHitBox.SetSize(20, 20);

    // sprite is bigger than the hitbox, so it needs to be drawn offset
    // so the hitbox sits at the character's feet/center, not top-left corner
    colliderOffsetX = (sprite.GetWidth() - collider.GetWidth()) / 2.0f;
    colliderOffsetY = sprite.GetHeight() - collider.GetHeight();

    sprite.SetPosition(
        collider.GetX() - colliderOffsetX,
        collider.GetY() - colliderOffsetY
    );
}

void Player::SetAttackHitboxFrames(int startFrame, int endFrame){
    attackHitboxStartFrame = startFrame;
    attackHitboxEndFrame = endFrame;
}

void Player::HandleInput(Input& input, float dt){

    moving = false;
    body.SetVelocityX(0.0f);

    if(!attacking){

        if(input.isKeyHeld(Key::A)){
            body.SetVelocityX(-moveSpeed);
            moving = true;
            flipped = true;
            sprite.FlipHorizontal();
        }

        if(input.isKeyHeld(Key::D)){
            body.SetVelocityX(moveSpeed);
            moving = true;
            flipped = false;
            sprite.ResetFlip();
        }

        if(input.isKeyPressed(Key::Space) && onGround){
            body.SetVelocityY(-700.0f);
            onGround = false;
            jump.Reset();
        }
    }

    if(input.isKeyPressed(Key::L) && !attacking){
        attacking = true;
        attack.Reset();
    }
}

void Player::Update(float dt){

    body.Update(dt);

    // NOTE: position is applied inside ResolveCollisions, not here.
    // Update() only handles gravity accumulation + animation/hitbox state.

    swordActive = false;

    if(attacking){
        sprite.SetAnimation(attack);
        attack.Update(dt);

        int frame = attack.GetCurrFrame();

        if(frame >= attackHitboxStartFrame && frame <= attackHitboxEndFrame){
            swordActive = true;

            float swordOffset = 5.0f;
            float swordX;

            if(flipped){
                swordX = collider.GetX() - swordOffset - swordHitBox.GetWidth();
            } else {
                swordX = collider.GetX() + collider.GetWidth() + swordOffset;
            }



            float swordY = (collider.GetY() - 25) + sprite.GetHeight() / 2.0f - swordHitBox.GetHeight() / 2.0f;

            swordHitBox.SetPosition(swordX, swordY);
        }

        if(frame == 5){
            attacking = false;
        }
    }
    else if(!onGround){
        sprite.SetAnimation(jump);
        jump.Update(dt);
    }
    else if(moving){
        sprite.SetAnimation(walk);
        walk.Update(dt);
    }
    else {
        sprite.SetAnimation(idle);
        idle.Update(dt);
    }

}

void Player::ResolveCollisions(std::vector<Collider>& grounds, float dt){

    //--------------------------------------------------
    // HORIZONTAL — apply X, then resolve X collisions
    //--------------------------------------------------
    //
    float previousY = collider.GetY();

    collider.SetPosition(
        collider.GetX() + body.GetVelocityX() * dt,
        collider.GetY()
    );

    for(auto& ground : grounds){
        if(!collider.Intersects(ground))
            continue;

        if(body.GetVelocityX() > 0){
            collider.SetPosition(ground.GetX() - collider.GetWidth(), collider.GetY());
            break;
        } else if(body.GetVelocityX() < 0){
            collider.SetPosition(ground.GetX() + ground.GetWidth(), collider.GetY());
            break;
        }
    }

    //--------------------------------------------------
    // VERTICAL — apply Y, then resolve Y collisions (with ground tolerance)
    //--------------------------------------------------

    collider.SetPosition(
        collider.GetX(),
        collider.GetY() + body.GetVelocityY() * dt
    );

    onGround = false;

    for(auto& ground : grounds){


        if(!collider.Intersects(ground))
            continue;

        if(body.GetVelocityY() >= 0)
        {
            collider.SetPosition(collider.GetX(), ground.GetY() - collider.GetHeight());
            body.SetVelocityY(0.0f);
            onGround = true;

            break;
        }
        else
        {
            collider.SetPosition(collider.GetX(), ground.GetY() + ground.GetHeight());
            body.SetVelocityY(0.0f);

            break;
        }
    }

    sprite.SetPosition(
        collider.GetX() - colliderOffsetX,
        collider.GetY() - colliderOffsetY
    );
}

void Player::Draw(Renderer& renderer){

    // renderer.DrawRect(
    //     collider.GetX(), collider.GetY(),
    //     collider.GetWidth(), collider.GetHeight(),
    //     255, 0, 0
    // );
    //
    // if(swordActive){
    //     renderer.DrawRect(
    //         swordHitBox.GetX(), swordHitBox.GetY(),
    //         swordHitBox.GetWidth(), swordHitBox.GetHeight(),
    //         255, 255, 0
    //     );
    // }

    sprite.Draw(renderer);
}
