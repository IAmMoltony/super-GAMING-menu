#include "loader.hpp"
#include "../blank_item.hpp"
#include "../nlohmann/json.hpp"
#include "../separator_item.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Menu loadConfig(std::string configFile)
{
    Menu menu;

    std::ifstream configFileStream(configFile);
    json data = json::parse(configFileStream);
    json items = data["items"];

    for (json item : items) {
        std::string itemKind = item["kind"];

        if (itemKind == "blank") {
            menu.addItem(new BlankMenuItem(item));
        } else if (itemKind == "separator") {
            menu.addItem(new SeparatorMenuItem(item));
        } else {
            std::cerr << "Unknown item kind '" << itemKind << "'." << std::endl;
        }
    }

    return menu;
}
