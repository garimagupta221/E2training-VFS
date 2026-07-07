#include "EchoCommand.h"
#include <iostream>

const std::string OVERWRITE_FLAG = ">";
const std::string APPEND_FLAG = ">>";

EchoCommand::EchoCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void EchoCommand::execute(const std::vector<std::string> &arguments) {
  if (arguments.size() < 2) {
    std::cout << std::endl;
    return;
  }

  std::string content;
  std::string filePath;
  RedirectionMode redirectionMode = NONE;

  for (auto iterator = arguments.begin() + 1; iterator != arguments.end();
       iterator++) {
    if ((*iterator == OVERWRITE_FLAG || *iterator == APPEND_FLAG) &&
        (iterator + 1) != arguments.end()) {
      redirectionMode = (*iterator == APPEND_FLAG) ? APPEND : OVERWRITE;
      filePath = *(iterator + 1);
      iterator++;
    } else {
      if (content.empty() == false) {
        content += " ";
      }
      content += *iterator;
    }
  }

  if (redirectionMode == NONE) {
    std::cout << content << std::endl;
    return;
  }

  fileSystem.createFile(filePath);
  auto resolvedFile = fileSystem.resolveFile(filePath);
  if (resolvedFile == nullptr) {
    std::cout << "echo: cannot open: " << filePath << std::endl;
    return;
  }

  if (redirectionMode == APPEND) {
    if (resolvedFile->getSize() > 0) {
      resolvedFile->appendContent("\n" + content);
    } else {
      resolvedFile->appendContent(content);
    }
  } else {
    resolvedFile->setContent(content);
  }

  fileSystem.save();
}
