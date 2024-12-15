#include "Player.h"

void Player::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) 
    {
        switch (event.key.keysym.sym) 
        {
        case SDLK_UP:
            _velocity.y = -1;
            break;
        case SDLK_DOWN:
            _velocity.y = 1;
            break;
        case SDLK_LEFT:
            _velocity.x = -1;
            break;
        case SDLK_RIGHT:
            _velocity.x = 1;
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP) 
    {
        switch (event.key.keysym.sym) 
        {
        case SDLK_UP:
        case SDLK_DOWN:
            _velocity.y = 0;
            break;
        case SDLK_LEFT:
        case SDLK_RIGHT:
            _velocity.x = 0;
            break;
        default:
            break;
        }
    }
}

void Player::update(float deltaTime)
{
    _position.x += _velocity.x * _speed * deltaTime;
    _position.y += _velocity.y * _speed * deltaTime;
}

void Player::render(SDL_Renderer* renderer) const
{
    if (_texture) 
    {
        SDL_Rect srcRect = { 0, 0, 100, 59 }; // Assuming the entire texture is 100x59

        Vector2f screenPos = _camera->worldToScreen(_position);
        SDL_Rect destRect = { static_cast<int>(screenPos.x), 
                              static_cast<int>(screenPos.y),
                              100, 59 }; // Position and size on screen

        SDL_RenderCopy(renderer, _texture, &srcRect, &destRect);
    }
}
