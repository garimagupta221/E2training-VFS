#include "ConcreteCommandFactory.h"
#include "CatCommand.h"
#include "CdCommand.h"
#include "EchoCommand.h"
#include "FindCommand.h"
#include "HelpCommand.h"
#include "LsCommand.h"
#include "MkdirCommand.h"
#include "PwdCommand.h"
#include "RmCommand.h"
#include "TouchCommand.h"

ConcreteCommandFactory::ConcreteCommandFactory(FileSystem &fileSystem)
    : fileSystem(fileSystem) {
  commandMap["mkdir"] = MKDIR;
  commandMap["touch"] = TOUCH;
  commandMap["ls"] = LS;
  commandMap["cd"] = CD;
  commandMap["pwd"] = PWD;
  commandMap["rm"] = RM;
  commandMap["cat"] = CAT;
  commandMap["echo"] = ECHO;
  commandMap["find"] = FIND;
  commandMap["help"] = HELP;
}

std::unique_ptr<ICommand>
ConcreteCommandFactory::createCommand(const std::string &name) {
  auto it = commandMap.find(name);
  if (it == commandMap.end()) {
    return nullptr;
  }

  auto command = it->second;
  switch (command) {
  case MKDIR:
    return std::make_unique<MkdirCommand>(fileSystem);
  case TOUCH:
    return std::make_unique<TouchCommand>(fileSystem);
  case LS:
    return std::make_unique<LsCommand>(fileSystem);
  case CD:
    return std::make_unique<CdCommand>(fileSystem);
  case PWD:
    return std::make_unique<PwdCommand>(fileSystem);
  case RM:
    return std::make_unique<RmCommand>(fileSystem);
  case CAT:
    return std::make_unique<CatCommand>(fileSystem);
  case ECHO:
    return std::make_unique<EchoCommand>(fileSystem);
  case FIND:
    return std::make_unique<FindCommand>(fileSystem);
  case HELP:
    return std::make_unique<HelpCommand>(fileSystem);
  default:
    return nullptr;
  }
}
