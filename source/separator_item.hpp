#pragma once

#include "menu_item.hpp"
#include "gaming_types.hpp"

class SeparatorMenuItem : public MenuItem
{
public:
    SDL_Color color;
    SDL_Color hoverColor;
    int thickness;
    int hoverThickness;
    int size;
    int hoverSize;
    GamingAlign align;
    GamingAlign hoverAlign;
    int padding;
    int hoverPadding;

    SeparatorMenuItem(SDL_Color color, SDL_Color hoverColor, int thickness, int hoverThickness, int size, int hoverSize, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding);
    ~SeparatorMenuItem();

    virtual void draw(SDL_Renderer *renderer, int y, int windowWidth, int windowHeight, bool isHovered) override;
};
