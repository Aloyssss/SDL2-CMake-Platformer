#pragma once

/* Includes */
#include "Header.h"
#include "Vector2.h"

/* Entity abstract class definition */
class Entity {
public:
    // Constructor / Destructor
    Entity(float x = 0, float y = 0)
        : _position(x, y), _isActive(true) { }
    virtual ~Entity() = default;

    // Core methods
    virtual void handleEvent(const SDL_Event& event) = 0;  // Handle specific events
    virtual void update(float deltaTime) = 0;              // Update the entity's state
    virtual void render(SDL_Renderer* renderer) const = 0; // Render the entity

    // Utility methods
    void setPosition(float x, float y) { _position.x = x; _position.y = y; }
    void setPosition(const Vector2f& newPosition) { _position = newPosition; }
    Vector2f getPosition() const { return _position; }

    void setActive(bool active) { _isActive = active; }
    bool getActive() const { return _isActive; }

protected:
    Vector2f _position; // Position of the entity
    bool _isActive;     // Whether the entity is active or not
};