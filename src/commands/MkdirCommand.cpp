#include "MkdirCommand.h"
#include <iostream>

MkdirCommand::MkdirCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void MkdirCommand::execute(const std::vector<std::string> &arguments) {
  if (arguments.size() < 2) {
    std::cout << "Too few arguments" << std::endl;
    return;
  }

  for (auto iterator = arguments.begin() + 1; iterator != arguments.end();
       iterator++) {
    if (!fileSystem.createDirectory(*iterator)) {
      std::cout << "Cannot create directory: " << *iterator << std::endl;
    }
  }
}
