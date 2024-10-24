#pragma once

#include <SDL2/SDL.h>

enum class MenuItemAction
{
    Exit,
    None
};

class MenuItem
{
public:
    MenuItem();
    ~MenuItem();

    virtual void draw(SDL_Renderer *renderer, int y, int windowWidth, int windowHeight, bool isHovered);
    virtual MenuItemAction onInteract(void);
};
