#include "BackgroundLayer.h"
#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(float x, float y, float scrollSpeed, SDL_Texture* texture)
    : Entity(x, y), _scrollSpeed(scrollSpeed), _texture(texture), _scrollOffset(0), _screenWidth(800), _screenHeight(600)
{
    SDL_QueryTexture(_texture, NULL, NULL, &_tileWidth, &_tileHeight);
}

void BackgroundLayer::handleEvent(const SDL_Event& event)
{
}

void BackgroundLayer::update(float deltaTime)
{
    _scrollOffset += _scrollSpeed * deltaTime;

    if (_scrollOffset >= _tileWidth)
    {
        _scrollOffset -= _tileWidth;
    }
    else if (_scrollOffset < 0)
    {
        _scrollOffset += _tileWidth;
    }
}

void BackgroundLayer::render(SDL_Renderer* renderer) const
{
    if (!_texture)
    {
        return;
    }

    SDL_Rect srcRect;
    SDL_Rect destRect;

    int currentOffset = static_cast<int>(_scrollOffset) % _tileWidth;

    for (int x = -currentOffset; x < _screenWidth; x += _tileWidth) {
        srcRect = { 0, 0, _tileWidth, _tileHeight };
        destRect = { x, 0, _tileWidth, _screenHeight };

        SDL_RenderCopy(renderer, _texture, &srcRect, &destRect);
    }
}
