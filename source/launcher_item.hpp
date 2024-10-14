#pragma once

#include "text_item.hpp"
#include "gaming_launcher.hpp"

class LauncherMenuItem : public TextMenuItem
{
private:
    GamingLauncher *mLauncher;
    SDL_Texture *mIcon;
    GamingAlign mIconAlign;
    GamingAlign mHoverIconAlign;
    int mIconPadding;
    int mHoverIconPadding;

public:
    LauncherMenuItem(SDL_Color color, SDL_Color hoverColor, std::string text, std::string hoverText, GamingAlign align, GamingAlign hoverAlign, GamingAlign iconAlign, GamingAlign hoverIconAlign, int padding, int hoverPadding, int iconPadding, int hoverIconPadding, std::string iconPath, TTF_Font *font, SDL_Renderer *renderer, GamingLauncher *launcher);
    LauncherMenuItem(SDL_Color color, SDL_Color hoverColor, std::string text, std::string hoverText, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding, TTF_Font *font, SDL_Renderer *renderer, GamingLauncher *launcher);
    ~LauncherMenuItem();

    virtual void draw(SDL_Renderer *renderer, int y, int windowWidth, int windowHeight, bool isHovered) override;
    virtual void onInteract() override;
};
