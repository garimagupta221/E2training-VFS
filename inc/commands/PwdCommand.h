#pragma once
#include "FileSystem.h"
#include "ICommand.h"


class PwdCommand : public ICommand {
public:
  explicit PwdCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
};
