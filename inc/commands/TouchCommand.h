#pragma once
#include "interfaces/ICommand.h"
#include "FileSystem.h"

class TouchCommand : public ICommand {
public:
  explicit TouchCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
};
