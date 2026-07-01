#include "commands/PwdCommand.h"
#include <iostream>

PwdCommand::PwdCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void PwdCommand::execute(const std::vector<std::string> &arguments) {
  std::cout << fileSystem.getCurrentPath() << std::endl;
}
