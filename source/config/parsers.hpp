#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "../gaming_types.hpp"
#include "../nlohmann/json.hpp"

SDL_Color parseColor(nlohmann::json colorJson);
GamingAlign parseAlign(std::string alignString);
