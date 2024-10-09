#include "launcher_item.hpp"
#include <cstdlib>

LauncherMenuItem::LauncherMenuItem(SDL_Color color, SDL_Color hoverColor, std::string text, std::string hoverText, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding, TTF_Font *font, SDL_Renderer *renderer, GamingLauncher *launcher) : TextMenuItem(color, hoverColor, text, hoverText, align, hoverAlign, padding, hoverPadding, font, renderer), mLauncher(launcher)
{
}

void LauncherMenuItem::draw(SDL_Renderer *renderer, int y, bool isHovered)
{
    TextMenuItem::draw(renderer, y, isHovered);
}

void LauncherMenuItem::onInteract(void)
{
    mLauncher->launch();
}
