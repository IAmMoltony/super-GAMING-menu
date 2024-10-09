#include "gaming_launcher_lutris.hpp"
#include <cstdlib>

GamingLauncherLutris::GamingLauncherLutris(std::string lutrisId) : mLutrisId(lutrisId)
{
}

void GamingLauncherLutris::launch(void)
{
    std::system(std::string("lutris lutris:rungame/" + mLutrisId).c_str());
}
