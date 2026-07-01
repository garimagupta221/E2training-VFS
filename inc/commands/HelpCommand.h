#pragma once
#include "interfaces/ICommand.h"
#include "FileSystem.h"

class HelpCommand : public ICommand {
public:
  explicit HelpCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;

  void showHelp() const;
  void showCommandHelp(const std::string &command) const;
};
