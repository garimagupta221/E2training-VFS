#pragma once
#include "ICommand.h"
#include "FileSystem.h"

class CatCommand : public ICommand {
public:
  explicit CatCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
};
