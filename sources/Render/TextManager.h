#pragma once

/* Includes */
#include "../Utils/Header.h"

/* TextManager class definition */
class TextManager
{
public:
    // Constructor / Destructor
    TextManager(SDL_Renderer* renderer);
    ~TextManager();

    // Font management
    bool loadFont(const std::string& fontName, const std::string& filePath, int fontSize);
    void unloadFont(const std::string& fontName);

    // Render text
    void renderText(const std::string& fontName, const std::string& text, SDL_Color color, SDL_Rect dest);

    // Cleanup
    void cleanup();

private:
    SDL_Renderer* _renderer; // Renderer for drawing text
    std::unordered_map<std::string, TTF_Font*> _fonts; // Font collection
};
