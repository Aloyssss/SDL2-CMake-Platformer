#include "TextManager.h"

TextManager::TextManager(SDL_Renderer* renderer)
    : _renderer(renderer)
{
    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
    }
}

TextManager::~TextManager()
{
    cleanup();
    TTF_Quit();
}

bool TextManager::loadFont(const std::string& fontName, const std::string& filePath, int fontSize)
{
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font '" << fontName << "': " << TTF_GetError() << std::endl;
        return false;
    }
    _fonts[fontName] = font;
    return true;
}

void TextManager::unloadFont(const std::string& fontName)
{
    auto it = _fonts.find(fontName);
    if (it != _fonts.end()) {
        TTF_CloseFont(it->second);
        _fonts.erase(it);
    }
}

void TextManager::renderText(const std::string& fontName, const std::string& text, SDL_Color color, SDL_Rect dest)
{
    auto it = _fonts.find(fontName);
    if (it == _fonts.end()) {
        std::cerr << "Font '" << fontName << "' not found. Unable to render text." << std::endl;
        return;
    }

    TTF_Font* font = it->second;
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surf) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surf);
    if (!texture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surf);
        return;
    }

    dest.w = surf->w;
    dest.h = surf->h;

    SDL_RenderCopy(_renderer, texture, nullptr, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surf);
}

void TextManager::cleanup()
{
    for (auto& pair : _fonts) {
        TTF_CloseFont(pair.second);
    }
    _fonts.clear();
}
