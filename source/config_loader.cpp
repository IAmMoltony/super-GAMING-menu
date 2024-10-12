#include "config_loader.hpp"
#include "blank_item.hpp"
#include "nlohmann/json.hpp"
#include "separator_item.hpp"
#include <fstream>
#include <iostream>
#include <map>

using json = nlohmann::json;

static std::map<std::string, GamingAlign> stringAlignTable = {
    {"left", GamingAlign::Left},
    {"center", GamingAlign::Center},
    {"right", GamingAlign::Right}
};

static SDL_Color parseColor(json colorJson)
{
    Uint8 r, g, b, a;

    if (!colorJson.contains("r")) {
        std::cerr << "Error parsing color " << colorJson << ": required 'r' field not found" << std::endl;
        return {255, 255, 255, 255};
    }
    if (colorJson["r"].is_number()) {
        r = colorJson["r"];
    } else {
        std::cerr << "Error parsing color " << colorJson << ": field 'r' is not a number" << std::endl;
        return {255, 255, 255, 255};
    }

    if (!colorJson.contains("g")) {
        std::cerr << "Error parsing color " << colorJson << ": required 'g' field not found" << std::endl;
        return {255, 255, 255, 255};
    }
    if (colorJson["g"].is_number()) {
        g = colorJson["g"];
    } else {
        std::cerr << "Error parsing color " << colorJson << ": field 'g' is not a number" << std::endl;
        return {255, 255, 255, 255};
    }

    if (!colorJson.contains("b")) {
        std::cerr << "Error parsing color " << colorJson << ": required 'b' field not found" << std::endl;
        return {255, 255, 255, 255};
    }
    if (colorJson["b"].is_number()) {
        b = colorJson["b"];
    } else {
        std::cerr << "Error parsing color " << colorJson << ": field 'b' field is not a number" << std::endl;
        return {255, 255, 255, 255};
    }

    if (colorJson.contains("a")) { // the alpha field is optional
        if (colorJson["a"].is_number()) {
            a = colorJson["a"];
        } else {
            std::cerr << "Error parsing color " << colorJson << ": field 'a' is not a number" << std::endl;
            return {255, 255, 255, 255};
        }
    } else {
        a = 255;
    }

    return {r, g, b, a};
}

static GamingAlign parseAlign(std::string alignString)
{
    auto align = stringAlignTable.find(alignString);
    if (align != stringAlignTable.end()) {
        return align->second;
    }
    std::cerr << "Unknown alignment type: '" << alignString << "'." << std::endl;
    return GamingAlign::Left;
}

std::ostream &operator<<(std::ostream &os, const SDL_Color &color)
{
    os << "(r=" << (int)color.r << " g=" << (int)color.g << " b=" << (int)color.b << " a=" << (int)color.a << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const GamingAlign &align)
{
    switch (align) {
    case GamingAlign::Left:
        os << "Left Align";
        break;
    case GamingAlign::Center:
        os << "Center Align";
        break;
    case GamingAlign::Right:
        os << "Right Align";
        break;
    default:
        os << "Illegal Align";
        break;
    }

    return os;
}

Menu loadConfig(std::string configFile)
{
    Menu menu;

    std::ifstream configFileStream(configFile);
    json data = json::parse(configFileStream);
    json items = data["items"];

    for (json item : items) {
        std::string itemKind = item["kind"];

        if (itemKind == "blank") {
            std::cout << "adding blank item" << std::endl;
            menu.addItem(new BlankMenuItem());
        } else if (itemKind == "separator") {
            SDL_Color color = {255, 255, 255, 255};
            SDL_Color hoverColor;
            int thickness = 1;
            int hoverThickness;
            int size = 85;
            int hoverSize;
            GamingAlign align = GamingAlign::Center;
            GamingAlign hoverAlign;
            int padding = 10;
            int hoverPadding;

            if (item.contains("color") && item["color"].is_object()) {
                color = parseColor(item["color"]);
            }

            if (item.contains("hover_color") && item["hover_color"].is_object()) {
                hoverColor = parseColor(item["hover_color"]);
            } else {
                hoverColor = color;
            }

            if (item.contains("thickness") && item["thickness"].is_number()) {
                thickness = item["thickness"];
            }

            if (item.contains("hover_thickness") && item["hover_thickness"].is_number()) {
                hoverThickness = item["hover_thickness"];
            } else {
                hoverThickness = thickness;
            }

            if (item.contains("size") && item["size"].is_number()) {
                size = item["size"];
            }

            if (item.contains("hover_size") && item["hover_size"].is_number()) {
                hoverSize = item["hover_size"];
            } else {
                hoverSize = size;
            }

            if (item.contains("align") && item["align"].is_string()) {
                align = parseAlign(item["align"]);
            }

            if (item.contains("hover_align") && item["hover_align"].is_string()) {
                hoverAlign = parseAlign(item["hover_align"]);
            } else {
                hoverAlign = align;
            }

            if (item.contains("padding") && item["padding"].is_number()) {
                padding = item["padding"];
            }

            if (item.contains("hover_padding") && item["hover_padding"].is_number()) {
                hoverPadding = item["hover_padding"];
            } else {
                hoverPadding = padding;
            }

            std::cout << "adding separator with color: " << color << " hover color: " << hoverColor << " thickness: " << thickness << " hover thickness: " << hoverThickness << " size: " << size << " hover size: " << hoverSize << " align: " << align << " hover align: " << hoverAlign << " padding: " << padding << " hover padding: " << hoverPadding << std::endl;

            menu.addItem(new SeparatorMenuItem(color, hoverColor, thickness, hoverThickness, size, hoverSize, align, hoverAlign, padding, hoverPadding));
        } else {
            std::cerr << "Unknown item kind '" << itemKind << "'." << std::endl;
        }
    }

    return menu;
}
