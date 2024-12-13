#pragma once

/* Includes */
#include "Header.h"
#include "Entity.h"
#include "Player.h"

/* BackgroundLayer class definition */
class BackgroundLayer : public Entity
{
public:
    BackgroundLayer(float x, float y, float scrollSpeed, SDL_Texture* texture);

    // Core methods override
    void handleEvent(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) const override;

    // Getters / Setters
    void setScrollSpeed(float newSpeed) { _scrollSpeed = newSpeed; }
    void setTexture(SDL_Texture* newTexture) { _texture = newTexture; }

private:
    SDL_Texture* _texture;
    Player* _player;

    int _screenWidth;
    int _screenHeight;
    int _tileWidth;
    int _tileHeight;
    float _scrollSpeed;
    float _scrollOffset;
};