#include "gaming_launcher_command.hpp"
#include <cstdlib>

GamingLauncherCommand::GamingLauncherCommand(std::string command) : mCommand(command)
{
}

void GamingLauncherCommand::launch(void)
{
    std::system(mCommand.c_str());
}
