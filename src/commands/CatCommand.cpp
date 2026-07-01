#include "commands/CatCommand.h"
#include <iostream>

CatCommand::CatCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void CatCommand::execute(const std::vector<std::string> &arguments) {
  if (arguments.size() < 2) {
    std::cout << "cat: Too few arguments" << std::endl;
    return;
  }

  bool endsWithNewline = true;
  for (auto iterator = arguments.begin() + 1; iterator != arguments.end();
       iterator++) {
    auto targetFile = fileSystem.resolveFile(*iterator);
    if (targetFile) {
      auto fileContent = targetFile->getContent();
      std::cout << fileContent;
      if (!fileContent.empty()) {
        endsWithNewline = (fileContent.back() == '\n');
      }
    } else {
      std::cout << "cat: " << *iterator << ":No such file or directory"
                << std::endl;
      endsWithNewline = true;
    }
  }

  if (!endsWithNewline) {
    std::cout << std::endl;
  }
}
