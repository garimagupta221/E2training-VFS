#include "commands/TouchCommand.h"
#include <iostream>

TouchCommand::TouchCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void TouchCommand::execute(const std::vector<std::string> &arguments) {
  if (arguments.size() < 2) {
    std::cout << "touch: missing file operand" << std::endl;
    return;
  }

  for (auto iterator = arguments.begin() + 1; iterator != arguments.end();
       iterator++) {
    if (!fileSystem.createFile(*iterator)) {
      std::cout << "touch: Cannot create file " << *iterator << std::endl;
    }
  }
}
