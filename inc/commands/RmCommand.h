#pragma once
#include "interfaces/ICommand.h"
#include "FileSystem.h"

class RmCommand : public ICommand {
public:
  explicit RmCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
};
