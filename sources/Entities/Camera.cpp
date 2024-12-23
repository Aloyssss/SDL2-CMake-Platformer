#include "Camera.h"

Camera::Camera(int screenWidth, int screenHeight, int worldWidth, int worldHeight)
    : _view{ 0, 0, 640, 360 },
    _worldWidth(worldWidth), _worldHeight(worldHeight),
    _screenWidth(screenWidth), _screenHeight(screenHeight),
    lerpFactor(0.1f) 
{
}

void Camera::moveTo(int x, int y)
{
    _view.x = x - _view.w / 2;
    _view.y = y - _view.h / 2;
    clampToBounds();
}

void Camera::follow(int targetX, int targetY)
{
    int targetViewX = targetX - _view.w / 2;
    int targetViewY = targetY - _view.h / 2;

    _view.x += static_cast<int>((targetViewX - _view.x) * lerpFactor);
    _view.y += static_cast<int>((targetViewY - _view.y) * lerpFactor);

    clampToBounds();
}

void Camera::setLerpFactor(float factor)
{
    lerpFactor = factor;
}

SDL_Rect Camera::getView() const
{
    return _view;
}

void Camera::setWorldBounds(int width, int height)
{
    _worldWidth = width;
    _worldHeight = height;
}
