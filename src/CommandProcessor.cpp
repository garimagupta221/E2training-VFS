#include "CommandProcessor.h"
#include <iomanip>
#include <iostream>
#include <sstream>

CommandProcessor::CommandProcessor(FileSystem &fileSystem,
                                   ICommandFactory &commandFactory)
    : fileSystem(fileSystem), commandFactory(commandFactory) {}

std::vector<std::string>
CommandProcessor::tokenise(const std::string &inputLine) const {
  std::vector<std::string> parsedTokens;
  std::stringstream stream(inputLine);
  std::string currentToken;

  while (stream >> std::quoted(currentToken)) {
    parsedTokens.push_back(currentToken);
  }

  return parsedTokens;
}


void CommandProcessor::run() {
  std::cout << "Virtual File System (VFS)" << std::endl;

  std::string inputLine;
  while (true) {
    std::cout << fileSystem.getCurrentPath() << "$ ";
    if (!std::getline(std::cin, inputLine)) {
      break;
    }

    const auto commandTokens = tokenise(inputLine);

    if (!commandTokens.empty()) {
      const std::string &commandName = commandTokens[0];

      if (commandName == "exit" || commandName == "quit") {
        std::cout << "Exiting VFS" << std::endl;
        break;
      }

      executeCommand(commandName, commandTokens);
    }
  }
}

void CommandProcessor::executeCommand(
    const std::string &commandName,
    const std::vector<std::string> &commandTokens) {
  auto command = commandFactory.createCommand(commandName);
  if (!command) {
    std::cout << commandName << ": Command not found" << std::endl;
  } else {
    command->execute(commandTokens);
  }
}
