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


    //// SUITE = CACA à ranger

    // init img
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Init player textures
    SDL_Surface* image = IMG_Load("./ressources/texture_atlas/hero-atlas.png");
    if (!image)
    {
        std::cerr << "Failed to load image.png: " << IMG_GetError() << std::endl;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_windowManager->getRenderer(), image);

    _player = std::make_unique<Player>(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, texture);

    ///////

    // Init fonts
    if (!_textManager->loadFont("default", "ressources/fonts/RobotoCondensed-Regular.ttf", 14))
    {
        return false;
    }

    _isRunning = true;
    return true;
}

void Game::cleanup()
{
    IMG_Quit();

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
    _player->update(_frameTimer.getFrameTime());
}

void Game::render()
{
    // Clear screen
    _windowManager->clear();

    // Draw game objects here
    // TODO : Draw game objects
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
