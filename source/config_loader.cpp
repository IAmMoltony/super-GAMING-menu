#include "config_loader.hpp"
#include "blank_item.hpp"
#include "gaming_launcher_command.hpp"
#include "gaming_launcher_lutris.hpp"
#include "nlohmann/json.hpp"
#include "separator_item.hpp"
#include "text_item.hpp"
#include "launcher_item.hpp"
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

static GamingLauncher *parseLauncher(json launcherJson)
{
    std::string launcherKind;

    if (!launcherJson.contains("kind")) {
        std::cerr << "Error parsing launcher " << launcherJson << ": required 'kind' field not found" << std::endl;
        return nullptr;
    }

    if (!launcherJson["kind"].is_string()) {
        std::cerr << "Error parsing launcher " << launcherJson << ": field 'kind' is not a string" << std::endl;
        return nullptr;
    }

    launcherKind = launcherJson["kind"];

    if (launcherKind == "command") {
        std::string command;
        if (!launcherJson.contains("command")) {
            std::cerr << "Error parsing command launcher " << launcherJson << ": required 'command' field not found" << std::endl;
            return nullptr;
        }
        if (!launcherJson["command"].is_string()) {
            std::cerr << "Error parsing command launcher " << launcherJson << ": field 'command' is not a string" << std::endl;
            return nullptr;
        }

        command = launcherJson["command"];
        return new GamingLauncherCommand(command);
    } else if (launcherKind == "lutris") {
        std::string lutrisId;
        if (!launcherJson.contains("lutris_id")) {
            std::cerr << "Error parsing Lutris launcher " << launcherJson << ": required 'lutris_id' field not found" << std::endl;
            return nullptr;
        }
        if (!launcherJson["lutris_id"].is_string()) {
            std::cerr << "Error parsing Lutris launcher " << launcherJson << ": field 'lutris_id' is not a string" << std::endl;
            return nullptr;
        }

        lutrisId = launcherJson["lutris_id"];
        return new GamingLauncherLutris(lutrisId);
    }

    std::cerr << "Error parsing launcher " << launcherJson << ": unknown launcher kind '" << launcherKind << "'" << std::endl;
    return nullptr;
}

Menu loadConfig(std::string configFile, TTF_Font *font, SDL_Renderer *renderer)
{
    Menu menu;

    std::ifstream configFileStream(configFile);
    json data = json::parse(configFileStream);
    json items = data["items"];

    for (json item : items) {
        std::string itemKind;

        if (!item.contains("kind")) {
            std::cerr << "Error parsing menu item " << item << ": required 'kind' field not found" << std::endl;
            continue;
        }

        if (!item["kind"].is_string()) {
            std::cerr << "Error parsing menu item " << item << ": field 'kind' is not a string" << std::endl;
            continue;
        }

        itemKind = item["kind"];

        if (itemKind == "blank") {
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

            menu.addItem(new SeparatorMenuItem(color, hoverColor, thickness, hoverThickness, size, hoverSize, align, hoverAlign, padding, hoverPadding));
        } else if (itemKind == "text") {
            SDL_Color color = {255, 255, 255, 255};
            SDL_Color hoverColor;
            std::string text = "";
            std::string hoverText;
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

            if (item.contains("text") && item["text"].is_string()) {
                text = item["text"];
            }

            if (item.contains("hover_text") && item["hover_text"].is_string()) {
                hoverText = item["hover_text"];
            } else {
                hoverText = text;
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
                padding = hoverPadding;
            }

            menu.addItem(new TextMenuItem(color, hoverColor, text, hoverText, align, hoverAlign, padding, hoverPadding, font, renderer));
        } else if (itemKind == "launcher") {
            SDL_Color textColor = {255, 255, 255, 255};
            SDL_Color hoverTextColor;
            std::string text = "";
            std::string hoverText;
            GamingAlign textAlign = GamingAlign::Center;
            GamingAlign hoverTextAlign;
            GamingAlign iconAlign = GamingAlign::Right;
            GamingAlign hoverIconAlign;
            int textPadding = 10;
            int hoverTextPadding;
            int iconPadding = 10;
            int hoverIconPadding;
            std::string iconPath;
            GamingLauncher *launcher;

            if (item.contains("text_color") && item["text_color"].is_object()) {
                textColor = parseColor(item["text_color"]);
            }

            if (item.contains("hover_text_color") && item["hover_text_color"].is_object()) {
                hoverTextColor = parseColor(item["hover_text_color"]);
            } else {
                hoverTextColor = textColor;
            }

            if (item.contains("text") && item["text"].is_string()) {
                text = item["text"];
            }

            if (item.contains("hover_text") && item["hover_text"].is_string()) {
                hoverText = item["hover_text"];
            } else {
                hoverText = text;
            }

            if (item.contains("text_align") && item["text_align"].is_string()) {
                textAlign = parseAlign(item["text_align"]);
            }

            if (item.contains("hover_text_align") && item["hover_text_align"].is_string()) {
                hoverTextAlign = parseAlign(item["hover_text_align"]);
            } else {
                hoverTextAlign = textAlign;
            }

            if (item.contains("icon_align") && item["icon_align"].is_string()) {
                iconAlign = parseAlign(item["icon_align"]);
            }

            if (item.contains("hover_icon_align") && item["hover_icon_align"].is_string()) {
                hoverIconAlign = parseAlign(item["hover_icon_align"]);
            } else {
                hoverIconAlign = iconAlign;
            }

            if (item.contains("text_padding") && item["text_padding"].is_number()) {
                textPadding = item["text_padding"];
            }

            if (item.contains("hover_text_padding") && item["hover_text_padding"].is_number()) {
                hoverTextPadding = item["hover_text_padding"];
            } else {
                hoverTextPadding = textPadding;
            }

            if (item.contains("icon_padding") && item["icon_padding"].is_number()) {
                iconPadding = item["icon_padding"];
            }

            if (item.contains("hover_icon_padding") && item["hover_icon_padding"].is_number()) {
                hoverIconPadding = item["hover_icon_padding"];
            } else {
                hoverIconPadding = iconPadding;
            }

            if (item.contains("icon_path") && item["icon_path"].is_string()) {
                iconPath = item["icon_path"];
            }

            if (item.contains("launcher")) {
                if (item["launcher"].is_object()) {
                    launcher = parseLauncher(item["launcher"]);
                } else {
                    std::cerr << "Error parsing launcher item " << item << ": field 'launcher' is not an object" << std::endl;
                    continue;
                }
            } else {
                std::cerr << "Error parsing launcher item " << item << ": required 'launcher' field not found " << std::endl;
                continue;
            }

            if (iconPath.size() == 0) {
                menu.addItem(new LauncherMenuItem(textColor, hoverTextColor, text, hoverText, textAlign, hoverTextAlign, textPadding, hoverTextPadding, font, renderer, launcher));
            } else {
                menu.addItem(new LauncherMenuItem(textColor, hoverTextColor, text, hoverText, textAlign, hoverTextAlign, iconAlign, hoverIconAlign, textPadding, hoverTextPadding, iconPadding, hoverIconPadding, iconPath, font, renderer, launcher));
            }
        } else {
            std::cerr << "Unknown item kind '" << itemKind << "'." << std::endl;
        }
    }

    return menu;
}
