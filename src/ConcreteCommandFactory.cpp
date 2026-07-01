#include "ConcreteCommandFactory.h"
#include "commands/CatCommand.h"
#include "commands/CdCommand.h"
#include "commands/EchoCommand.h"
#include "commands/FindCommand.h"
#include "commands/LsCommand.h"
#include "commands/MkdirCommand.h"
#include "commands/PwdCommand.h"
#include "commands/RmCommand.h"
#include "commands/TouchCommand.h"
#include "commands/HelpCommand.h"

ConcreteCommandFactory::ConcreteCommandFactory(FileSystem &fileSystem)
    : fileSystem(fileSystem) {}

std::unique_ptr<ICommand>
ConcreteCommandFactory::createCommand(const std::string &name) {
  if (name == "mkdir") {
    return std::make_unique<MkdirCommand>(fileSystem);
  }
  if (name == "touch") {
    return std::make_unique<TouchCommand>(fileSystem);
  }
  if (name == "ls") {
    return std::make_unique<LsCommand>(fileSystem);
  }
  if (name == "cd") {
    return std::make_unique<CdCommand>(fileSystem);
  }
  if (name == "pwd") {
    return std::make_unique<PwdCommand>(fileSystem);
  }
  if (name == "rm") {
    return std::make_unique<RmCommand>(fileSystem);
  }
  if (name == "cat") {
    return std::make_unique<CatCommand>(fileSystem);
  }
  if (name == "echo") {
    return std::make_unique<EchoCommand>(fileSystem);
  }
  if (name == "find") {
    return std::make_unique<FindCommand>(fileSystem);
  }
  if (name == "help") {
    return std::make_unique<HelpCommand>(fileSystem);
  }
  return nullptr;
}
