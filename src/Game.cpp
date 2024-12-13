#include "Game.h"

Game::Game()
    : _isRunning(false)
{
}

Game::~Game()
{
    cleanup();
}

bool Game::init(const char* title, int width, int height)
{
    // SDL init, must be the first init called
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Init engine components
    _windowManager = std::make_unique<WindowManager>("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    _textManager = std::make_unique<TextManager>(_windowManager->getRenderer());
    _textureManager = std::make_unique<TextureManager>(_windowManager->getRenderer());

    // Init player textures
    _textureManager->loadTexture("player_atlas", "./ressources/texture_atlas/hero-atlas.png");
    _player = std::make_unique<Player>(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, _textureManager->getTexture("player_atlas"));

    _textureManager->loadTexture("bg1", "./ressources/texture_atlas/background.png");
    _bgLayer1 = std::make_unique<BackgroundLayer>(0.f, 0.f, 200.f, _textureManager->getTexture("bg1"));

    // Init fonts
    _textManager->loadFont("default", "ressources/fonts/RobotoCondensed-Regular.ttf", 14);

    _isRunning = true;
    return true;
}

void Game::cleanup()
{
    // Quit functions
    if (SDL_WasInit(SDL_INIT_EVERYTHING))
        SDL_Quit();
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT) 
        {
            _isRunning = false;
        }
        
        // TODO : Handle other events
        _player->handleEvent(event);
    }
}

void Game::update()
{
    // TODO : Add game logic, update game objects
    _player->update(_frameTimer.getFrameTimeS());

    // Background update based on player position
    _bgLayer1->setScrollSpeed((_player->getVelocity().x) * _player->getSpeed());
    _bgLayer1->update(_frameTimer.getFrameTimeS());
}

void Game::render()
{
    // Clear screen
    _windowManager->clear();

    // TODO : Draw game objects

    // Draw background
    _bgLayer1->render(_windowManager->getRenderer());

    // Draw entities
    _player->render(_windowManager->getRenderer());

    // Show window debug infos (fps and average fps)
#ifdef _DEBUG
    std::string fpsStr = "Current FPS: " + std::to_string(_frameTimer.getCurrentFPS());
    std::string avgStr = "Average FPS: " + std::to_string(_frameTimer.getAverageFPS());
    SDL_Color fg = { 255, 255, 255 };
    SDL_Rect dest = { 10, 10, 0, 0 };
    _textManager->renderText("default", fpsStr, fg, dest);
    dest.y += 24;
    _textManager->renderText("default", avgStr, fg, dest);
    dest.y += 24;
    _textManager->renderText("default", "Version 0.1.12", fg, dest);
#endif

    // Draw everything to the screen
    _windowManager->display();
}

void Game::run()
{
   while (_isRunning)
    {
       // frame start timing
       _frameTimer.startFrame();
        
       // game loop
        handleEvents();
        update();
        render();

        // end frame timing and statistics update
        _frameTimer.endFrame(1000/FRAME_RATE);
    }
}
