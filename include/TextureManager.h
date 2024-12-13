#pragma once

/* Includes */
#include "Header.h"

/* TextureManager class definition */
class TextureManager
{
public:
    // Constructor / Destructor
    TextureManager(SDL_Renderer* renderer);
    ~TextureManager();

    // Texture management
    bool loadTexture(const std::string& texName, const std::string& filePath);
    void unloadTexture(const std::string& texName);
    SDL_Texture* getTexture(const std::string& texName);

    // Render texture

    // Cleanup
    void cleanup();

private:
    SDL_Renderer* _renderer; // Renderer for drawing textures
    std::unordered_map<std::string, SDL_Texture*> _textures; // Texture collection
};
