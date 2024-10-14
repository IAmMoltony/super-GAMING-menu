#pragma once

#include "menu.hpp"
#include <string>
#include <SDL2/SDL_ttf.h>

Menu loadConfig(std::string configFile, TTF_Font *font, SDL_Renderer *renderer, int *windowWidth, int *windowHeight);
