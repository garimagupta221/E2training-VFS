#pragma once
#include "interfaces/ICommand.h"
#include "FileSystem.h"

class LsCommand : public ICommand {
public:
  explicit LsCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
  void printDirectoryContents(const std::shared_ptr<Directory> &directory) const;
};
