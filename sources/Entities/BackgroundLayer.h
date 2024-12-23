#pragma once

/* Includes */
#include "../Utils/Header.h"
#include "GameObject.h"
#include "Camera.h"

/* BackgroundLayer class definition */
class BackgroundLayer : public GameObject
{
public:
    BackgroundLayer(float x, float y, float scrollSpeed, SDL_Texture* texture, Camera* camera);

    // Core methods override
    void handleEvent(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) const override;

    // Getters / Setters
    void setScrollSpeed(float newSpeed) { _scrollSpeed = newSpeed; }
    void setTexture(SDL_Texture* newTexture) { _texture = newTexture; }
    SDL_Texture* getTexture() { return _texture; }
    int getTileWidth() { return _tileWidth; }

private:
    SDL_Texture* _texture;
    Camera* _camera;

    int _screenWidth;
    int _screenHeight;
    int _tileWidth;
    int _tileHeight;
    float _scrollSpeed;
    float _scrollOffset;
};