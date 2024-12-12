#include "Game.h"

Game::Game()
    : _windowManager(nullptr), _textManager(nullptr), _isRunning(false) {
}

Game::~Game()
{
    cleanup();
}

bool Game::init(const char* title, int width, int height)
{
    // SDL init, must be the first init called
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Init engine components
    _windowManager = std::make_unique<WindowManager>("Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    _textManager = std::make_unique<TextManager>(_windowManager->getRenderer());

    // Init fonts
    if (!_textManager->loadFont("default", "ressources/fonts/RobotoCondensed-Regular.ttf", 14)) {
        return false;
    }

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
    }
}

void Game::update()
{
    // TODO : Add game logic, update game objects
}

void Game::render()
{
    // Clear screen
    _windowManager->clear();

    // Draw game objects here
    // TODO : Draw game objects

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
        // Start frame timing
        /*frameData.totalFrames++;
        frameData.frameStart = SDL_GetTicks();*/
       _frameTimer.startFrame();

        
        handleEvents();
        update();
        render();

        //// Calculate frame time
        //frameData.frameTime = SDL_GetTicks() - frameData.frameStart;

        //// Cap FPS to 60 by delaying if the frame was faster
        //if (frameData.frameTime < frameData.frameDelay)
        //{
        //    SDL_Delay(frameData.frameDelay - frameData.frameTime);
        //}

        //// Update statistics
        //frameData.totalFrameTicks += SDL_GetTicks() - frameData.frameStart;
        //frameData.framePerSecond = 1000.0f / (SDL_GetTicks() - frameData.frameStart);
        _frameTimer.endFrame(1000/FRAME_RATE);
    }
}
