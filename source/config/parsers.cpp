#include "parsers.hpp"
#include <map>
#include <iostream>

using json = nlohmann::json;

static std::map<std::string, GamingAlign> stringAlignTable = {
    {"left", GamingAlign::Left},
    {"center", GamingAlign::Center},
    {"right", GamingAlign::Right}
};

SDL_Color parseColor(json colorJson)
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

GamingAlign parseAlign(std::string alignString)
{
    auto align = stringAlignTable.find(alignString);
    if (align != stringAlignTable.end()) {
        return align->second;
    }
    std::cerr << "Unknown alignment type: '" << alignString << "'." << std::endl;
    return GamingAlign::Left;
}
