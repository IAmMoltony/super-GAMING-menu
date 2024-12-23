#pragma once

#include "text_item.hpp"
#include <vector>

class NestMenuItem : public TextMenuItem
{
private:
    SDL_Texture *mIcon;
    GamingAlign mIconAlign;
    GamingAlign mHoverIconAlign;
    int mIconPadding;
    int mHoverIconPadding;

public:
    std::vector<MenuItem *> items;

    NestMenuItem(SDL_Color textColor, SDL_Color hoverTextColor, std::string text, std::string hoverText, GamingAlign textAlign, GamingAlign hoverTextAlign, GamingAlign iconAlign, GamingAlign hoverIconAlign, int textPadding, int hoverTextPadding, int iconPadding, int hoverIconPadding, std::string iconPath, TTF_Font *font, SDL_Renderer *renderer, std::initializer_list<MenuItem *> items);
    NestMenuItem(SDL_Color textColor, SDL_Color hoverTextColor, std::string text, std::string hoverText, GamingAlign textAlign, GamingAlign hoverTextAlign, int textPadding, int hoverTextPadding, TTF_Font *font, SDL_Renderer *renderer, std::initializer_list<MenuItem *> items);
    NestMenuItem(SDL_Color textColor, SDL_Color hoverTextColor, std::string text, std::string hoverText, GamingAlign textAlign, GamingAlign hoverTextAlign, GamingAlign iconAlign, GamingAlign hoverIconAlign, int textPadding, int hoverTextPadding, int iconPadding, int hoverIconPadding, std::string iconPath, TTF_Font *font, SDL_Renderer *renderer, std::vector<MenuItem *> items);
    NestMenuItem(SDL_Color textColor, SDL_Color hoverTextColor, std::string text, std::string hoverText, GamingAlign textAlign, GamingAlign hoverTextAlign, int textPadding, int hoverTextPadding, TTF_Font *font, SDL_Renderer *renderer, std::vector<MenuItem *> items);
    ~NestMenuItem();

    virtual void draw(SDL_Renderer *renderer, int y, int windowWidth, int windowHeight, bool isHovered) override;
    virtual MenuItemAction onInteract(void) override;
};
