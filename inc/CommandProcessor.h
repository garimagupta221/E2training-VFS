
#pragma once
#include "FileSystem.h"
#include "interfaces/ICommandFactory.h"
#include <string>
#include <vector>

class CommandProcessor {
public:
  CommandProcessor(FileSystem &fileSystem, ICommandFactory &commandFactory);
  void run();

private:
  FileSystem &fileSystem;
  ICommandFactory &commandFactory;

  std::vector<std::string> tokenise(const std::string &inputLine) const;
  void executeCommand(const std::string &commandName,
                      const std::vector<std::string> &commandTokens);
};
