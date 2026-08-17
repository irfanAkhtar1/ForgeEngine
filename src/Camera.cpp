#include "Camera.h"

Camera::Camera(int width, int height){
    viewW = width;
    viewH = height;
}

void Camera::SetPosition(float x, float y){
    this->x = x - viewW * 0.5f;
    this->y = y - viewH * 0.5f;
}

void Camera::Follow(float targetX, float targetY, float smoothness){
    float targetCamX = targetX - viewW * 0.5f;
    float targetCamY = targetY - viewH * 0.5f;

    x += (targetCamX - x) * smoothness;
    y += (targetCamY - y) * smoothness;

    if(worldW > 0){
        if(x < 0) x = 0;
        if(x > worldW - viewW) x = worldW - viewW;
    }

    if(worldH > 0){
        if(y < 0) y = 0;
        if(y > worldH - viewH) y = worldH - viewH;
    }

    if(worldW < viewW) x = 0;
    if(worldH < viewH) y = 0;
}
