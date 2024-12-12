#include "WindowManager.h"

WindowManager::WindowManager(const std::string& title, int width, int height)
	: _window(nullptr), _renderer(nullptr)
{
	createWindow(title, width, height);
}

WindowManager::~WindowManager()
{
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
}

void WindowManager::clear()
{
    SDL_RenderClear(_renderer);
}

void WindowManager::display()
{
    SDL_RenderPresent(_renderer);
}

void WindowManager::createWindow(const std::string& title, int width, int height)
{
    _window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!_window)
    {
        throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer)
    {
        throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
    }
}
