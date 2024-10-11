#include "menu_item.hpp"

using json = nlohmann::json;

MenuItem::MenuItem()
{
}

MenuItem::MenuItem(json itemJson)
{
    configure(itemJson);
}

MenuItem::~MenuItem()
{
}

void MenuItem::configure(json itemJson)
{
}

void MenuItem::draw(SDL_Renderer *renderer, int y, bool isHovered)
{
}

void MenuItem::onInteract(void)
{
}
