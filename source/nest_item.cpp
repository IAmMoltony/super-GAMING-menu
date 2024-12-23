#include "nest_item.hpp"
#include "menu_item.hpp"

NestMenuItem::NestMenuItem(SDL_Color textColor, SDL_Color hoverTextColor, std::string text, std::string hoverText, GamingAlign textAlign, GamingAlign hoverTextAlign, GamingAlign iconAlign, GamingAlign hoverIconAlign, int textPadding, int hoverTextPadding, int iconPadding, int hoverIconPadding, std::string iconPath, TTF_Font *font, SDL_Renderer *renderer, std::initializer_list<MenuItem *> items) : TextMenuItem(textColor, hoverTextColor, text, hoverText, textAlign, hoverTextAlign, textPadding, hoverTextPadding, font, renderer), mIconAlign(iconAlign), mHoverIconAlign(hoverIconAlign), mIconPadding(iconPadding), mHoverIconPadding(hoverIconPadding), items(items)
{

}

void NestMenuItem::draw(SDL_Renderer *renderer, int y, int windowWidth, int windowHeight, bool isHovered)
{
}

MenuItemAction NestMenuItem::onInteract(void)
{
    return MenuItemAction::None;
}
