#pragma once

#include <SDL2/SDL.h>
#include "nlohmann/json.hpp"

class MenuItem
{
public:
    MenuItem();
    MenuItem(nlohmann::json itemJson);
    ~MenuItem();

    virtual void configure(nlohmann::json itemJson);
    virtual void draw(SDL_Renderer *renderer, int y, bool isHovered);
    virtual void onInteract(void);
};
