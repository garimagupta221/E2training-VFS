#include "Application.h"
#include "CommandProcessor.h"
#include "ConcreteCommandFactory.h"
#include "FileSystem.h"
#include "FileSystemPersistence.h"

const std::string FILENAME = "vfs_persistence.txt";

int main() {
  FileSystemPersistence persistance(FILENAME);
  FileSystem fileSystem(persistance);
  ConcreteCommandFactory commandFactory(fileSystem);
  CommandProcessor commandProcessor(fileSystem, commandFactory);
  Application application(fileSystem, commandProcessor);
  application.start();
  return 0;
}
