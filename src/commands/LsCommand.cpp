#include "commands/LsCommand.h"
#include <iostream>
#include <iterator>


LsCommand::LsCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void LsCommand::printDirectoryContents(
    const std::shared_ptr<Directory> &directory) const {
  if (!directory) {
    return;
  }
  const auto &children = directory->getChildren();
  for (auto it = children.begin(); it != children.end(); ++it) {
    std::cout << (*it)->getName();
    if (std::next(it) != children.end()) {
      std::cout << "\t";
    }
  }
  if (!children.empty()) {
    std::cout << std::endl;
  }
}

void LsCommand::execute(const std::vector<std::string> &arguments) {
  if (arguments.size() < 1) {
    std::cout << "ls: Too few arguments" << std::endl;
    return;
  }

  if (arguments.size() > 2) {
    std::cout << "ls: Too many arguments" << std::endl;
    return;
  }

  if (arguments.size() == 1) {
    auto directory = fileSystem.getCurrentWorkingDirectory();
    printDirectoryContents(directory);
  } else {
    auto path = arguments[1];
    auto directory = fileSystem.resolveDirectory(path);
    if (directory) {
      printDirectoryContents(directory);
    } else {
      std::cout << "ls: directory not found: " << path << std::endl;
    }
  }
}
