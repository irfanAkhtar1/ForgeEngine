#include "PhysicsBody.h"


void PhysicsBody::Update(float dt){

    velocityY += grv * dt;

    if(velocityY > terminalVelocity){

        velocityY = terminalVelocity;

    }
}


void PhysicsBody::SetVelocity(float vx, float vy){

    velocityX = vx;
    velocityY = vy;

}


void PhysicsBody::AddVelocity(float vx, float vy){

    velocityX += vx;
    velocityY += vy;

}


float PhysicsBody::GetVelocityX() const{

    return velocityX;

}

float PhysicsBody::GetVelocityY() const{

    return velocityY;

}


void PhysicsBody::SetVelocityX(float vx){
    velocityX = vx;
}

void PhysicsBody::SetVelocityY(float vy){
    velocityY = vy;
}


void PhysicsBody::SetGravity(float g){

    grv = g;

}


void PhysicsBody::SetTerminalVelocity(float velocity){

    terminalVelocity = velocity;

}
