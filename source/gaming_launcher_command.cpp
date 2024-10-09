#include "gaming_launcher_command.hpp"
#include <boost/process.hpp>

GamingLauncherCommand::GamingLauncherCommand(std::string command) : mCommand(command)
{
}

void GamingLauncherCommand::launch(void)
{
    boost::process::child process(mCommand);
    process.detach();
}
