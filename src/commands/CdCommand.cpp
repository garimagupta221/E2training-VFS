#include "commands/CdCommand.h"
#include "VFSConstants.h"
#include <iostream>

CdCommand::CdCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void CdCommand::execute(const std::vector<std::string> &arguments) {
  std::string directoryPath =
      (arguments.size() >= 2) ? arguments[1] : ROOT_DIRECTORY;
  if (!fileSystem.changeDirectory(directoryPath)) {
    std::cout << "cd: Cannot change to: " << directoryPath << std::endl;
  }
}
