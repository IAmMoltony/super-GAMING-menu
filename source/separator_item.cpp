#include "separator_item.hpp"

SeparatorMenuItem::SeparatorMenuItem(SDL_Color color, SDL_Color hoverColor, int thickness, int hoverThickness, int size, int hoverSize, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding) : color(color), hoverColor(hoverColor), thickness(thickness), hoverThickness(hoverThickness), size(size), hoverSize(hoverSize), align(align), hoverAlign(hoverAlign), padding(padding), hoverPadding(hoverPadding)
{
}

SeparatorMenuItem::~SeparatorMenuItem()
{
}

void SeparatorMenuItem::draw(SDL_Renderer *renderer, int y, int windowWidth, int windowHeight, bool isHovered)
{
    SDL_Color realColor = isHovered ? hoverColor : color;
    int realThickness = isHovered ? hoverThickness : thickness;
    int realSize = isHovered ? hoverSize : size;
    GamingAlign realAlign = isHovered ? hoverAlign : align;
    int realPadding = isHovered ? hoverPadding : padding;

    int pixelSize = (int)(realSize / 100.0 * (double)windowWidth);
    int halfPixelSize = pixelSize / 2;
    int lineY = y + 16 - (realThickness / 2);

    int x1, x2;
    switch (realAlign) {
    case GamingAlign::Center:
        x1 = (windowWidth / 2) - halfPixelSize;
        x2 = (windowWidth / 2) + halfPixelSize;
        break;
    case GamingAlign::Left:
        x1 = realPadding;
        x2 = realPadding + pixelSize;
        break;
    case GamingAlign::Right:
        x1 = windowWidth - pixelSize - realPadding;
        x2 = windowWidth - realPadding;
        break;
    }

    SDL_SetRenderDrawColor(renderer, realColor.r, realColor.g, realColor.b, realColor.a);
    for (int i = 0; i < realThickness; i++) {
        SDL_RenderDrawLine(renderer, x1, lineY + i, x2, lineY + i);
    }
}
