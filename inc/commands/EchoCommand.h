#pragma once
#include "ICommand.h"
#include "FileSystem.h"

class EchoCommand : public ICommand {
public:
  enum RedirectionMode { NONE, OVERWRITE, APPEND };

  explicit EchoCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
};
