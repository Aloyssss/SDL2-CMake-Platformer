#include "RenderWindow.h"

RenderWindow::RenderWindow(const std::string& title, const int screenWidth, const int screenHeight, const int baseWidth, const int baseHeight)
	: _window(nullptr), _renderer(nullptr), _renderTarget(nullptr), _baseWidth(baseWidth), _baseHeight(baseHeight)
{
    createWindow(title, screenWidth, screenHeight);
    createRenderer(_window);
    createRenderTarget(_renderer, baseWidth, baseHeight);
}

RenderWindow::~RenderWindow()
{
    if (_renderer)
        SDL_DestroyRenderer(_renderer);
    if (_window)
        SDL_DestroyWindow(_window);
    if (_renderTarget)
        SDL_DestroyTexture(_renderTarget);
}

void RenderWindow::beginRender()
{
    // Définir la texture de base comme cible de rendu
    SDL_SetRenderTarget(_renderer, _renderTarget);

    // Effacer la texture de base
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void RenderWindow::EndRender()
{
    // Retourner au rendu par défaut (l'écran)
    SDL_SetRenderTarget(_renderer, nullptr);

    // Obtenir la taille actuelle de la fenêtre
    int windowWidth, windowHeight;
    SDL_GetWindowSize(_window, &windowWidth, &windowHeight);

    // Calculer le ratio d'échelle
    float scaleX = (float)windowWidth / _baseWidth;
    float scaleY = (float)windowHeight / _baseHeight;
    float scale = std::min(scaleX, scaleY);

    // Calculer la taille mise à l'échelle et centrer
    int scaledWidth = _baseWidth * scale;
    int scaledHeight = _baseHeight * scale;

    SDL_Rect dstRect = {
        (windowWidth - scaledWidth) / 2,
        (windowHeight - scaledHeight) / 2,
        scaledWidth, scaledHeight
    };

    // Copier le rendu mis à l'échelle à l'écran
    SDL_RenderCopy(_renderer, _renderTarget, nullptr, &dstRect);

    // Afficher le rendu final
    SDL_RenderPresent(_renderer);
}

void RenderWindow::createWindow(const std::string& title, const int width, const int height)
{
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, SDL_WINDOW_SHOWN);
    if (!_window)
    {
        std::cerr << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
    }
}

void RenderWindow::createRenderer(SDL_Window* window)
{
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

void RenderWindow::createRenderTarget(SDL_Renderer* renderer, const int baseWidth, const int baseHeight)
{
    // Create a render target texture at the base resolution to draw to
    _renderTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        baseWidth, baseHeight);
    if (!_renderTarget)
    {
        std::cerr << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
    }
}
