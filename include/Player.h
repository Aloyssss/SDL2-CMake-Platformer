#pragma once

/* Includes */
#include "Header.h"
#include "Entity.h"

/* Player class definition */
class Player : public Entity 
{
public:
    Player(float x, float y, SDL_Texture* texture)
        : Entity(x, y), _speed(200.0f), _texture(texture) { }

    // Core methods override
    void handleEvent(const SDL_Event& event) override;
    void update(float deltaTime) override;
    void render(SDL_Renderer* renderer) const override;

    // Getters / Setters
    Vector2f getVelocity() const { return _velocity; }
    void setVelocity(const Vector2f newVelocity) { _velocity = newVelocity; }

    float getSpeed() const { return _speed; }
    void setSpeed(const float newSpeed) { _speed = newSpeed; }

    void setTexture(SDL_Texture* newTexture) { _texture = newTexture; }

private:
    Vector2f _velocity = { 0, 0 }; // Movement direction
    float _speed;                  // Movement speed in pixels/second
    SDL_Texture* _texture;
};