#include "Animation.h"
#include <SDL2/SDL.h>


void Animation::SetTexture(Texture& texture){

    this->texture = &texture;

}


void Animation::SetFrame(int width, int height){

    frameWidth = width; 
    frameHeight = height;

}


void Animation::SetFrameCount(int count){

    totalFrame = count;

}


void Animation::SetFPS(float fps){

    this->fps = fps;

}


void Animation::Update(float dt){

    timer += dt;


    
    if(timer >= (1.0f/fps)){
        
        currFrame++;
        currFrame %= totalFrame;

        timer = 0.0f;

    }

}

int Animation::GetFrameX() const{

    return currFrame * frameWidth;

}

int Animation::GetFrameY() const{

    return 0;

}

int Animation::GetFrameWidth() const{

    return frameWidth;

}


int Animation::GetFrameHeight() const{

    return frameHeight;

}



void Animation::Reset(){

    currFrame = 0;
    timer = 0.0f;

}


