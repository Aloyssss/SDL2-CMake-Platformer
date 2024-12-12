#pragma once

/* Includes */
#include "Header.h"

/* Window class definition */
class WindowManager
{
public:
    // Constructor and Destructor
    WindowManager(const std::string& title, int width, int height);
    ~WindowManager();

    // Delete copy constructor and assignment operator
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    // Utility functions
    void clear();
    void display();

    // Getters
    SDL_Window* getSDLWindow() const { return _window; }
    SDL_Renderer* getRenderer() const { return _renderer; }

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    SDL_Color _clearColor;

    // Private helper function
    void createWindow(const std::string& title, int width, int height);
};