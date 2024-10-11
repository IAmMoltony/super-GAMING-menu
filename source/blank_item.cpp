#include "blank_item.hpp"

using json = nlohmann::json;

BlankMenuItem::BlankMenuItem()
{
}

BlankMenuItem::BlankMenuItem(json itemJson) : MenuItem(itemJson)
{
}

BlankMenuItem::~BlankMenuItem()
{
}
