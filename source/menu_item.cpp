#include "menu_item.hpp"

MenuItem::MenuItem()
{
}

MenuItem::~MenuItem()
{
}

void MenuItem::draw(SDL_Renderer *renderer, int y, int windowWidth, int windowHeight, bool isHovered)
{
}

MenuItemAction MenuItem::onInteract(void)
{
    return MenuItemAction::None;
}
