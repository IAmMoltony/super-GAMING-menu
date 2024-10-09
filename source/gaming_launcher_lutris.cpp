#include "gaming_launcher_lutris.hpp"
#include <boost/process.hpp>

GamingLauncherLutris::GamingLauncherLutris(std::string lutrisId) : mLutrisId(lutrisId)
{
}

void GamingLauncherLutris::launch(void)
{
    boost::process::child process("lutris lutris:rungame/" + mLutrisId);
    process.detach();
}
