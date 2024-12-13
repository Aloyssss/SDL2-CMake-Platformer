#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer)
    : _renderer(renderer)
{
    // init img
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
    }
}

TextureManager::~TextureManager()
{
    cleanup();
    IMG_Quit();
}

bool TextureManager::loadTexture(const std::string& texName, const std::string& filePath)
{
    SDL_Surface* image = IMG_Load(filePath.c_str());
    if (!image)
    {
        std::cerr << "Failed to load image.png: " << IMG_GetError() << std::endl;
        return false;
    }
    _textures[texName] = SDL_CreateTextureFromSurface(_renderer, image);
    return true;
}

void TextureManager::unloadTexture(const std::string& texName)
{
    auto it = _textures.find(texName);
    if (it != _textures.end()) {
        _textures.erase(it);
    }
}

SDL_Texture* TextureManager::getTexture(const std::string& texName)
{
    return _textures[texName];
}

void TextureManager::cleanup()
{
    _textures.clear();
}
