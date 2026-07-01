#include "Application.h"

Application::Application(FileSystem &fileSystem,
                         CommandProcessor &commandProcessor)
    : fileSystem(fileSystem), commandProcessor(commandProcessor) {}

void Application::start() {
  fileSystem.initializeFileSystem();
  commandProcessor.run();
  fileSystem.save();
}
