#include "Collider.h"



Collider::Collider(float x, float y, float w, float h){

    this->x = x;
    this->y = y;

    width = w;
    height = h;

}


void Collider::SetPosition(float x, float y){

    this->x = x;
    this->y = y;

}


void Collider::SetSize(float w, float h){
    
    width = w;
    height = h;

}

bool Collider::Intersects(const Collider&other) const{

    return !(

        x + width <= other.x || x >= other.x + other.width ||

        y + height <= other.y || y >= other.y + other.height

    );

}


float Collider::GetX() const{

    return x;

}


float Collider::GetY() const{

    return y;

}


float Collider::GetWidth() const{

    return width;

}

float Collider::GetHeight() const{

    return height;

}



