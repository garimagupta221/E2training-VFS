
#pragma once
#include "FileSystem.h"
#include "ICommandFactory.h"
#include <unordered_map>

class ConcreteCommandFactory : public ICommandFactory {
public:
  enum CommandType {
    MKDIR,
    TOUCH,
    LS,
    CD,
    PWD,
    RM,
    CAT,
    ECHO,
    FIND,
    HELP,
    UNKNOWN
  };

  explicit ConcreteCommandFactory(FileSystem &fileSystem);
  std::unique_ptr<ICommand> createCommand(const std::string &name) override;

private:
  FileSystem &fileSystem;
  std::unordered_map<std::string, CommandType> commandMap;
};
