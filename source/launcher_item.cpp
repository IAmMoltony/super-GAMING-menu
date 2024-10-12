#include "launcher_item.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

LauncherMenuItem::LauncherMenuItem(SDL_Color color, SDL_Color hoverColor, std::string text, std::string hoverText, GamingAlign align, GamingAlign hoverAlign, GamingAlign iconAlign, GamingAlign hoverIconAlign, int padding, int hoverPadding, int iconPadding, int hoverIconPadding, std::string iconPath, TTF_Font *font, SDL_Renderer *renderer, GamingLauncher *launcher) : TextMenuItem(color, hoverColor, text, hoverText, align, hoverAlign, padding, hoverPadding, font, renderer), mLauncher(launcher), mIconAlign(iconAlign), mHoverIconAlign(hoverIconAlign), mIconPadding(iconPadding), mHoverIconPadding(hoverIconPadding)
{
    mIcon = IMG_LoadTexture(renderer, iconPath.c_str());
    if (!mIcon) {
        std::cerr << "Failed to load image '" << iconPath << "': " << IMG_GetError() << std::endl;
    }
}

LauncherMenuItem::LauncherMenuItem(SDL_Color color, SDL_Color hoverColor, std::string text, std::string hoverText, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding, TTF_Font *font, SDL_Renderer *renderer, GamingLauncher *launcher) : TextMenuItem(color, hoverColor, text, hoverText, align, hoverAlign, padding, hoverPadding, font, renderer), mLauncher(launcher), mIcon(nullptr),  mIconAlign(GamingAlign::Left), mHoverIconAlign(GamingAlign::Left), mIconPadding(0), mHoverIconPadding(0)
{
}

LauncherMenuItem::~LauncherMenuItem()
{
    SDL_DestroyTexture(mIcon);
}

void LauncherMenuItem::draw(SDL_Renderer *renderer, int y, bool isHovered)
{
    TextMenuItem::draw(renderer, y, isHovered);

    if (mIcon) {
        GamingAlign realAlign = isHovered ? mHoverIconAlign : mIconAlign;
        int realPadding = isHovered ? mHoverIconPadding : mIconPadding;

        int x;
        switch (realAlign) {
        case GamingAlign::Left:
            x = realPadding;
            break;
        case GamingAlign::Center:
            x = 234;
            break;
        case GamingAlign::Right:
            x = 468 - realPadding;
            break;
        }

        SDL_Rect destRect = {x, y, 32, 32};
        SDL_RenderCopy(renderer, mIcon, nullptr, &destRect);
    }
}

void LauncherMenuItem::onInteract(void)
{
    if (mLauncher)
        mLauncher->launch();
}
