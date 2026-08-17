#include "Sprite.h"
#include "Animation.h"

void Sprite::SetTexture(Texture& texture){

    this->texture = &texture;

    width = texture.GetWidth();
    height = texture.GetHeight();

}

void Sprite::SetPosition(float x, float y){

    this->x = x;
    this->y = y;

}

void Sprite::SetSize(float width, float height){

    this->width = width;
    this->height = height;

}

void Sprite::SetRotation(double angle){

    rotation = angle;

}

void Sprite::Draw(Renderer& renderer){

    if(texture == nullptr){
        return;
    }


    float drawX = x;
    float drawY = y;


    if(animation){
    
        texture->Draw(

            renderer,

            drawX,
            drawY,

            width,
            height,

            animation->GetFrameX(),
            animation->GetFrameY(),
            animation->GetFrameWidth(),
            animation->GetFrameHeight(),

            rotation,
            flip

        );

    }else{

        texture->Draw(

            renderer,

            drawX,
            drawY,

            width,
            height,

            rotation,
            flip

        );

    }


}


void Sprite::SetAnimation(Animation& animation){

    this->animation = &animation;
    this->texture = animation.GetTexture();

}


void Sprite::FlipHorizontal(){

    flip = SDL_FLIP_HORIZONTAL;

}

void Sprite::FlipVertical(){

    flip = SDL_FLIP_VERTICAL;

}

void Sprite::ResetFlip(){

    flip = SDL_FLIP_NONE;

}
