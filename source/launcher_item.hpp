#pragma once

#include "text_item.hpp"

class LauncherMenuItem : public TextMenuItem
{
public:
    std::string command;

    LauncherMenuItem(SDL_Color color, SDL_Color hoverColor, std::string text, std::string hoverText, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding, TTF_Font *font, SDL_Renderer *renderer, std::string command);

    virtual void draw(SDL_Renderer *renderer, int y, bool isHovered) override;
    virtual void onInteract() override;
};
