#pragma once

/* Standard includes */
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdexcept>
#include <unordered_map>

/* External includes */
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Vector2.h"
#include <json.hpp>

/* Constant parameters */
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FRAME_RATE = 60;