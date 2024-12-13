#pragma once

/* Includes */
#include "WindowManager.h"
#include "TextManager.h"
#include "TextureManager.h"

#include "Player.h"
#include "BackgroundLayer.h"

/* FrameTimer class definition */
class FrameTimer
{
public:
	void startFrame() 
	{
		frameStart = SDL_GetTicks();
	}

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

	float getFrameTimeMs() const { return float(frameTime); }
	float getFrameTimeS() const { return float(frameTime) / 1000.f; }

	float getCurrentFPS() const { return framePerSecond; }
	float getAverageFPS() const { return totalFrames > 0 ? 1000.0f / ((float)totalFrameTicks / totalFrames) : 0.0f; }

private:
	Uint32 frameStart = 0;
	Uint32 frameTime = 0;
	Uint32 totalFrameTicks = 0;
	Uint32 totalFrames = 0;
	float framePerSecond = 0.f;
};

/* Game class definition */
class Game
{
public:
	// Constructor / Destructor
	Game();
	~Game();

	// Init functions
	bool init(const char* title, int width, int height);
	void cleanup();

	// Game loop functions
	void handleEvents();
	void update();
	void render();
	void run();

private:
	// Engine components variables
	std::unique_ptr<WindowManager> _windowManager;
	std::unique_ptr<TextManager> _textManager;
	std::unique_ptr<TextureManager> _textureManager;
	FrameTimer _frameTimer;

	// Game loop variables
	bool _isRunning;

	// Game objects
	std::unique_ptr<Player> _player;
	std::unique_ptr<BackgroundLayer> _bgLayer1;
};