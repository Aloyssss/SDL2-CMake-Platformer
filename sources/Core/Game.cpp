#include "Game.h"

Game::Game()
    : _isRunning(false)
{
}

Game::~Game()
{
    cleanup();
}

bool Game::init(std::string windowConfigFilename)
{
    // SDL init, must be the first init called
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Open window config file and checks if it is empty
    std::ifstream file(windowConfigFilename);
    if (!file.is_open()) {
        std::cerr << "Failed to open window config file: " << windowConfigFilename << std::endl;
        return false;
    }

    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Window config file is empty: " << windowConfigFilename << std::endl;
        return false;
    }

    nlohmann::json data;
    try {
        file >> data;
    }
    catch (nlohmann::json::parse_error& e) {
        throw std::runtime_error("JSON parse error: " + std::string(e.what()));
    }

    std::string title = data["title"].get<std::string>();
    int screenWidth = data["screen_width"].get<int>();
    int screenHeight = data["screen_height"].get<int>();
    int baseWidth = data["base_width"].get<int>();
    int baseHeight = data["base_height"].get<int>();
    float framerate = data["framerate"].get<float>();

    // Init engine component
    _renderWindow = std::make_unique<RenderWindow>(title, screenWidth, screenHeight, baseWidth, baseHeight);
    _textManager = std::make_unique<TextManager>(_renderWindow->getRenderer());
    _textureManager = std::make_unique<TextureManager>(_renderWindow->getRenderer());

    // Camera init
    _camera = std::make_unique<Camera>(baseWidth, baseHeight, 0, 0);
    _camera->setLerpFactor(0.05f);

    // Init map
    std::string tileset = "./ressources/map/spritesheet2.png";
    std::string json = "./ressources/map/map2.json";
    _tilemap = std::make_unique<Tilemap>(json, tileset, _renderWindow->getRenderer(), _camera.get());
    _camera->setWorldBounds(_tilemap->getWorldBounds().x, _tilemap->getWorldBounds().y);

    // Init player textures
    _textureManager->loadTexture("player_atlas", "./ressources/texture_atlas/hero-atlas.png");
    _player = std::make_unique<Player>(200, 200, _textureManager->getTexture("player_atlas"), _camera.get());

    _textureManager->loadTexture("bg1", "./ressources/texture_atlas/background.png");
    _bgLayer1 = std::make_unique<BackgroundLayer>(0.f, 0.f, 200.f, _textureManager->getTexture("bg1"), _camera.get());

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
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                _isRunning = false;
                break;
            default:
                break;
            }
        }
        
        // TODO : Handle other events
        _player->handleEvent(event);
    }
}

void Game::update()
{
    // TODO : Add game logic, update game objects

    // Camera update
    _camera->follow(_player->getPosition().x, _player->getPosition().y);

    _player->update(_frameTimer.getFrameTimeS());

    // Background update based on player position
    /*_bgLayer1->setScrollSpeed((_player->getVelocity().x) * _player->getSpeed());
    _bgLayer1->update(_frameTimer.getFrameTimeS());*/
}

void Game::render()
{
    // Clear screen
    _renderWindow->beginRender();
    // Draw background (_camera affects it too)
    //_bgLayer1->render(_windowManager->getRenderer());

    // Draw world
    _tilemap->render(_renderWindow->getRenderer());

    // Draw entities
    _player->render(_renderWindow->getRenderer());

    // Show window debug infos (fps and average fps)
#ifdef _DEBUG
    SDL_Rect defaultViewport = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderSetViewport(_renderWindow->getRenderer(), &defaultViewport); // Reset for debug UI
    std::string fpsStr = "Current FPS: " + std::to_string(_frameTimer.getCurrentFPS());
    std::string avgStr = "Average FPS: " + std::to_string(_frameTimer.getAverageFPS());
    SDL_Color fg = { 255, 255, 255 };
    SDL_Rect dest = { 10, 10, 0, 0 };
    _textManager->renderText("default", fpsStr, fg, dest);
    dest.y += 24;
    _textManager->renderText("default", avgStr, fg, dest);
    dest.y += 24;
    _textManager->renderText("default", VERSION, fg, dest);
#endif

    // Draw everything to the screen
    _renderWindow->EndRender();
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
