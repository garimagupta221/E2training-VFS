#pragma once
#include "ICommand.h"
#include "FileSystem.h"

class MkdirCommand : public ICommand {
public:
  explicit MkdirCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
};
