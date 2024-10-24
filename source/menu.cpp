#include "menu.hpp"

Menu::Menu() : mItemLists(), mBaseItems(), mHoveredItem(-1)
{
    mItemLists.push(&mBaseItems);
    mItems = mItemLists.top();
}

Menu::Menu(std::initializer_list<MenuItem *> items) : mItemLists(), mBaseItems(items), mHoveredItem(-1)
{
    mItemLists.push(&mBaseItems);
    mItems = mItemLists.top();
}

Menu::~Menu()
{
}

void Menu::draw(SDL_Renderer *renderer, int windowWidth, int windowHeight)
{
    for (size_t i = 0; i < mItems->size(); i++) {
        MenuItem *item = mItems->at(i);
        int itemY = i * 32;
        bool isHovered = i == mHoveredItem;
        if (isHovered) {
            SDL_Rect itemRect = {0, itemY, 500, 32};
            SDL_SetRenderDrawColor(renderer, 20, 20, 48, 255);
            SDL_RenderFillRect(renderer, &itemRect);
        }

        item->draw(renderer, itemY, windowWidth, windowHeight, isHovered);
    }
}

void Menu::addItem(MenuItem *item)
{
    mBaseItems.push_back(item);
}

void Menu::onMouseMove(int mouseX, int mouseY)
{
    mHoveredItem = -1;
    for (size_t i = 0; i < mItems->size(); i++) {
        MenuItem *item = mItems->at(i);
        int itemY = i * 32;
        if (mouseY >= itemY && mouseY < itemY + 32) {
            mHoveredItem = i;
        }
    }
}

void Menu::onMouseDown(int button)
{
    if (button == 1 && mHoveredItem >= 0) {
        mItems->at(mHoveredItem)->onInteract();
    }
}

void Menu::onKeyDown(SDL_Keycode key)
{
    if (key == SDLK_DOWN) {
        mHoveredItem++;
        if (mHoveredItem > mItems->size() - 1) {
            mHoveredItem--;
        }
    } else if (key == SDLK_UP) {
        mHoveredItem--;
        if (mHoveredItem < 0) {
            mHoveredItem = 0;
        }
    } else if (key == SDLK_RETURN && mHoveredItem >= 0) {
        mItems->at(mHoveredItem)->onInteract();
    }
}
