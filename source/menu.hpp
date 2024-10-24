#pragma once

#include "menu_item.hpp"
#include <initializer_list>
#include <vector>
#include <stack>

class Menu
{
private:
    std::stack<std::vector<MenuItem *> *> mItemLists;
    std::vector<MenuItem *> *mItems;
    std::vector<MenuItem *> mBaseItems;
    int mHoveredItem;
    bool mShouldQuit;

public:
    Menu();
    Menu(std::initializer_list<MenuItem *> items);
    ~Menu();

    void draw(SDL_Renderer *renderer, int windowWidth, int windowHeight);
    void addItem(MenuItem *item);
    void onMouseMove(int mouseX, int mouseY);
    void onMouseDown(int button);
    void onKeyDown(SDL_Keycode key);

    bool shouldQuit();
};
