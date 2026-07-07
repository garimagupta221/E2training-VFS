#include "RmCommand.h"
#include <iostream>

RmCommand::RmCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void RmCommand::execute(const std::vector<std::string> &arguments) {
  if (arguments.size() < 2) {
    std::cout << "rm: missing operand" << std::endl;
    return;
  }

  if (arguments[1] == "-r") {
    if (arguments.size() < 3) {
      std::cout << "rm: missing operand" << std::endl;
      return;
    }

    if (arguments.size() > 3) {
      std::cout << "rm: too many arguments" << std::endl;
      return;
    }

    fileSystem.removeDirectory(arguments[2]);
    return;
  }

  for (auto iterator = arguments.begin() + 1; iterator != arguments.end();
       iterator++) {
    fileSystem.removeFile(*iterator);
  }
}
