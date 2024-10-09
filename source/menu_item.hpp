#pragma once

#include <SDL2/SDL.h>

class MenuItem
{
public:
    MenuItem();
    ~MenuItem();

    virtual void draw(SDL_Renderer *renderer, int y, bool isHovered);
    virtual void onInteract(void);
};
