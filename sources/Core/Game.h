#pragma once

/* Includes */
#include "../Render/TextManager.h"
#include "../Render/TextureManager.h"
#include "../Render/RenderWindow.h"

#include "../Entities/Camera.h"
#include "../Entities/Player.h"
#include "../Entities/BackgroundLayer.h"
#include "../Entities/Tilemap.h"

/**
 * @class FrameTimer
 * @brief Manages frame timing and FPS calculations for the game loop.
 */
class FrameTimer
{
public:

	/**
	 * @brief Starts timing for the current frame.
	 */
	void startFrame() 
	{
		frameStart = SDL_GetTicks();
	}

	/**
	 * @brief Ends timing for the current frame and applies a delay to maintain the target frame rate.
	 * @param frameDelay The desired delay in milliseconds for the frame to achieve the target frame rate.
	 */
	void endFrame(Uint32 frameDelay) 
	{
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) 
		{
			SDL_Delay(frameDelay - frameTime);
			frameTime = SDL_GetTicks() - frameStart;
		}
		totalFrameTicks += frameTime;
		totalFrames++;
		framePerSecond = 1000.0f / (float)frameTime;
	}

	/**
	 * @brief Gets the duration of the current frame in milliseconds.
	 * @return The current frame time in milliseconds.
	 */
	float getFrameTimeMs() const { return float(frameTime); }

	/**
	 * @brief Gets the duration of the current frame in seconds.
	 * @return The current frame time in seconds.
	 */
	float getFrameTimeS() const { return float(frameTime) / 1000.f; }

	/**
	 * @brief Gets the current frames per second (FPS).
	 * @return The current FPS.
	 */
	float getCurrentFPS() const { return framePerSecond; }

	/**
	 * @brief Gets the average frames per second (FPS) since the game started.
	 * @return The average FPS.
	 */
	float getAverageFPS() const { return totalFrames > 0 ? 1000.0f / ((float)totalFrameTicks / totalFrames) : 0.0f; }

private:
	Uint32 frameStart = 0;         /// Start time of the current frame.
	Uint32 frameTime = 0;          /// Duration of the current frame.
	Uint32 totalFrameTicks = 0;    /// Accumulated time of all frames.
	Uint32 totalFrames = 0;        /// Total number of frames.
	float framePerSecond = 0.f;    /// Current FPS.
};

/**
 * @class Game
 * @brief Represents the main game engine, managing initialization, the game loop, and cleanup.
 */
class Game
{
public:
	/**
	 * @brief Constructor. Initializes game state.
	 */
	Game();

	/**
	 * @brief Destructor. Cleans up resources.
	 */
	~Game();

	/**
	 * @brief Initializes the game engine and its components.
	 * @param windowConfigFilename Path to the JSON configuration file for the window.
	 * @return True if initialization is successful, false otherwise.
	 */
	bool init(std::string windowConfigFilename);

	/**
	 * @brief Cleans up all resources and shuts down the engine.
	 */
	void cleanup();

	/**
	 * @brief Handles user input and events.
	 */
	void handleEvents();

	/**
	 * @brief Updates the game state and entities logic.
	 */
	void update();

	/**
	 * @brief Renders the game world, entities and UI to the screen.
	 */
	void render();

	/**
	 * @brief Runs the main game loop until the game is exited.
	 */
	void run();

private:
	// Engine components variables

	// Window, renderer and render target
	std::unique_ptr<RenderWindow> _renderWindow;

	// Timing and time variables
	FrameTimer _frameTimer;


	std::unique_ptr<TextManager> _textManager;
	std::unique_ptr<TextureManager> _textureManager;
	std::unique_ptr<Camera> _camera;

	// Game loop variables
	bool _isRunning;

	// Game objects
	std::unique_ptr<Tilemap> _tilemap;
	std::unique_ptr<Player> _player;
	std::unique_ptr<BackgroundLayer> _bgLayer1;
};