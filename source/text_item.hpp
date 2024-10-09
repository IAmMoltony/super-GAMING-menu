#pragma once

#include "menu_item.hpp"
#include "gaming_types.hpp"
#include <string>
#include <SDL2/SDL_ttf.h>

class TextMenuItem : public MenuItem
{
private:
    SDL_Texture *mTexture;
    SDL_Texture *mHoverTexture;
    int mTextureWidth;
    int mTextureHeight;
    int mHoverTextureWidth;
    int mHoverTextureHeight;

public:
    GamingAlign align;
    GamingAlign hoverAlign;
    int padding;
    int hoverPadding;

    TextMenuItem(SDL_Color color, SDL_Color hoverColor, std::string text, std::string hoverText, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding, TTF_Font *font, SDL_Renderer *renderer);
    ~TextMenuItem();

    virtual void draw(SDL_Renderer *renderer, int y, bool isHovered) override;
};
