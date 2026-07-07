#pragma once
#include "ICommand.h"
#include "FileSystem.h"

class CdCommand : public ICommand {
public:
  explicit CdCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
};
