#pragma once


class Collider{


public:

    Collider() = default;

    Collider(float x, float y, float w, float h);

    void SetPosition(float x, float y);

    void SetSize(float w, float h);

    bool Intersects(const Collider& other) const;

    float GetX() const;
    float GetY() const;

    float GetWidth() const;
    float GetHeight() const;


    bool IsDestroyed() const {
        return destroyed;
    }


    void Destroy(){
        destroyed = true;
    }


private:

    float x = 0.0f;
    float y = 0.0f;

    float width = 0.0f;
    float height = 0.0f;

    bool destroyed = false;

};



