
#pragma once
#include "FileSystem.h"
#include "interfaces/ICommandFactory.h"


class ConcreteCommandFactory : public ICommandFactory {
public:
  explicit ConcreteCommandFactory(FileSystem &fileSystem);
  std::unique_ptr<ICommand> createCommand(const std::string &name) override;

private:
  FileSystem &fileSystem;
};
