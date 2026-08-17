#pragma once

class Camera{

public:

    Camera(int width, int height);

    void Follow(float targetX, float targetY, float smoothness);

    void SetPosition(float x, float y);

    void SetViewSize(int width, int height){

        viewW = width;
        viewH = height;

    }

    void SetWorldSize(int width, int height){

        worldW = width;
        worldH = height;

    }

    float GetX() const{

        return x;

    }

    float GetY() const{

        return y;

    }

    int GetViewWidth() const{

        return viewW;

    }

    int GetViewHeight() const{

        return viewH;

    }

private:

    float x = 0.0f;
    float y = 0.0f;

    int viewW = 0;
    int viewH = 0;

    int worldW = 0;
    int worldH = 0;

};
