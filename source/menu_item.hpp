#pragma once

#include <SDL2/SDL.h>

class MenuItem
{
public:
    MenuItem();
    ~MenuItem();

    virtual void draw(SDL_Renderer *renderer, int y, bool isHovered) = 0;
    virtual void onInteract(void) = 0;
};
