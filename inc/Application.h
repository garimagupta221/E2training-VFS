
#pragma once
#include "CommandProcessor.h"
#include "FileSystem.h"


class Application {
public:
  Application(FileSystem &fileSystem, CommandProcessor &commandProcessor);
  void start();

private:
  FileSystem &fileSystem;
  CommandProcessor &commandProcessor;
};
