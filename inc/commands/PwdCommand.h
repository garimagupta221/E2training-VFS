#pragma once
#include "interfaces/ICommand.h"
#include "FileSystem.h"

class PwdCommand : public ICommand {
public:
  explicit PwdCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
};
