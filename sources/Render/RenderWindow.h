#pragma once

/* Includes */
#include "../Utils/Header.h"

/* Render window class definition */
class RenderWindow
{
public:
    // Constructor and Destructor
    RenderWindow(const std::string& title, const int screenWidth, const int screenHeight, const int baseWidth, const int baseHeight);
    ~RenderWindow();

    // Delete copy constructor and assignment operator
    RenderWindow(const RenderWindow&) = delete;
    RenderWindow& operator=(const RenderWindow&) = delete;

    // Utility functions
    void beginRender();
    void EndRender();

    // Getters / Setters
    SDL_Window* getWindow() const { return _window; }
    SDL_Renderer* getRenderer() const { return _renderer; }
    SDL_Texture* getRenderTarget() const { return _renderTarget; }
    void setClearColor(const SDL_Color newColor) { _clearColor = newColor; }

private:
    SDL_Window* _window;
    SDL_Texture* _renderTarget;
    SDL_Renderer* _renderer;
    SDL_Color _clearColor;

    int _baseWidth, _baseHeight;

    // Private helper functions
    void createWindow(const std::string& title, const int screenWidth, const int screenHeight);
    void createRenderer(SDL_Window* window);
    void createRenderTarget(SDL_Renderer* renderer, const int baseWidth, const int baseHeight);
};