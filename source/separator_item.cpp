#include "separator_item.hpp"
#include "config/parsers.hpp"

using json = nlohmann::json;

SeparatorMenuItem::SeparatorMenuItem(SDL_Color color, SDL_Color hoverColor, int thickness, int hoverThickness, int size, int hoverSize, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding) : color(color), hoverColor(hoverColor), thickness(thickness), hoverThickness(hoverThickness), size(size), hoverSize(hoverSize), align(align), hoverAlign(hoverAlign), padding(padding), hoverPadding(hoverPadding)
{
}

SeparatorMenuItem::~SeparatorMenuItem()
{
}

SeparatorMenuItem::SeparatorMenuItem(json itemJson) : MenuItem(itemJson)
{
}

void SeparatorMenuItem::configure(json itemJson)
{
    if (itemJson.contains("color") && itemJson.is_object()) {
        color = parseColor(itemJson["color"]);
    } else {
        color = {255, 255, 255, 255};
    }

    if (itemJson.contains("hover_color")) {
        hoverColor = parseColor(itemJson["hover_color"]);
    } else {
        color = {255, 255, 255, 255};
    }

    if (itemJson.contains("thickness") && itemJson["thickness"].is_number()) {
        thickness = itemJson["thickness"];
    } else {
        thickness = 1;
    }

    if (itemJson.contains("hover_thickness") && itemJson["hover_thickness"].is_number()) {
        hoverThickness = itemJson["hover_thickness"];
    } else {
        hoverThickness = 1;
    }

    if (itemJson.contains("size") && itemJson["size"].is_number()) {
        size = itemJson["size"];
    } else {
        size = 85;
    }

    if (itemJson.contains("hover_size") && itemJson["hover_size"].is_number()) {
        hoverSize = itemJson["hover_size"];
    } else {
        size = 85;
    }

    if (itemJson.contains("align") && itemJson["align"].is_string()) {
        align = parseAlign(itemJson["align"]);
    } else {
        align = GamingAlign::Center;
    }

    if (itemJson.contains("hover_align") && itemJson["hover_align"].is_string()) {
        hoverAlign = parseAlign(itemJson["align"]);
    } else {
        align = GamingAlign::Center;
    }

    if (itemJson.contains("padding") && itemJson["padding"].is_number()) {
        padding = itemJson["padding"];
    } else {
        padding = 0;
    }

    if (itemJson.contains("hover_padding") && itemJson["hover_padding"].is_number()) {
        hoverPadding = itemJson["hover_padding"];
    } else {
        hoverPadding = 0;
    }
}

void SeparatorMenuItem::draw(SDL_Renderer *renderer, int y, bool isHovered)
{
    SDL_Color realColor = isHovered ? hoverColor : color;
    int realThickness = isHovered ? hoverThickness : thickness;
    int realSize = isHovered ? hoverSize : size;
    GamingAlign realAlign = isHovered ? hoverAlign : align;
    int realPadding = isHovered ? hoverPadding : padding;

    int pixelSize = (int)(realSize / 100.0 * 500.0);
    int halfPixelSize = pixelSize / 2;
    int lineY = y + 16 - (realThickness / 2);

    int x1, x2;
    switch (realAlign) {
    case GamingAlign::Center:
        x1 = 250 - halfPixelSize;
        x2 = 250 + halfPixelSize;
        break;
    case GamingAlign::Left:
        x1 = realPadding;
        x2 = realPadding + pixelSize;
        break;
    case GamingAlign::Right:
        x1 = 500 - pixelSize - realPadding;
        x2 = 500 - realPadding;
        break;
    }

    SDL_SetRenderDrawColor(renderer, realColor.r, realColor.g, realColor.b, realColor.a);
    for (int i = 0; i < realThickness; i++) {
        SDL_RenderDrawLine(renderer, x1, lineY + i, x2, lineY + i);
    }
}
