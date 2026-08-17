#pragma once

class PhysicsBody{


public:

    void Update(float dt);

    void SetVelocity(float vx, float vy);
    void AddVelocity(float vx, float vy);

    float GetVelocityX() const;
    float GetVelocityY() const;


    void SetVelocityX(float vx);
    void SetVelocityY(float vy);


    void SetGravity(float grv);
    void SetTerminalVelocity(float velocity);


private:

    float velocityX = 0.0f;
    float velocityY = 0.0f;

    float grv = 1800.0f;
    float terminalVelocity = 800.0f;


};
