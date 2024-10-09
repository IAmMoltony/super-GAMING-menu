#pragma once

#include "gaming_launcher.hpp"
#include <string>

class GamingLauncherLutris : public GamingLauncher
{
private:
    std::string mLutrisId;

public:
    GamingLauncherLutris(std::string lutrisId);

    virtual void launch(void) override;
};
