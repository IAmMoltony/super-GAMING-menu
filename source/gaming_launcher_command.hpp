#pragma once

#include "gaming_launcher.hpp"
#include <string>

class GamingLauncherCommand : public GamingLauncher
{
private:
    std::string mCommand;

public:
    GamingLauncherCommand(std::string command);

    virtual void launch(void) override;
};
