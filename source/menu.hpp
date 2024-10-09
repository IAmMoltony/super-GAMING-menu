#pragma once

#include "menu_item.hpp"
#include <initializer_list>
#include <vector>

class Menu
{
private:
    std::vector<MenuItem *> mItems;
    int mHoveredItem;

public:
    Menu();
    Menu(std::initializer_list<MenuItem *> items);
    ~Menu();

    void draw(SDL_Renderer *renderer);
    void addItem(MenuItem *item);
    void onMouseMove(int mouseX, int mouseY);
    void onMouseDown(int button);
    void onKeyDown(SDL_Keycode key);
};
