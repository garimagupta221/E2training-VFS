#include "FileSystem.h"
#include "VFSConstants.h"
#include <iostream>

FileSystem::FileSystem(IFileSystemPersistence &persistance)
    : persistenceProvider(persistance) {}

void FileSystem::initializeFileSystem() {
  rootDirectory = persistenceProvider.deserialize();
  if (!rootDirectory) {
    rootDirectory = std::make_shared<Directory>(ROOT_DIRECTORY);
  }
  currentWorkingDirectory = rootDirectory;
}

void FileSystem::save() { persistenceProvider.serialize(*this); }

std::shared_ptr<Directory>
FileSystem::resolveDirectory(const std::string &directoryPath) const {
  if (directoryPath.empty() || directoryPath == ROOT_DIRECTORY) {
    return rootDirectory;
  }

  auto currentDirectory =
      (directoryPath[0] == PATH_SEPARATOR_CHAR) ? rootDirectory
                                                : currentWorkingDirectory;

  for (const auto &segment : Utility::splitPath(directoryPath)) {
    if (segment == ".") {
    } else if (segment == "..") {
      auto parent = currentDirectory->getParent().lock();
      if (parent) {
        currentDirectory = parent;
      }
    } else {
      auto child = currentDirectory->findChild(segment);
      if (!child ||
          child->getComponentType() != FileSystemComponentType::DIRECTORY) {
            std::cout << "cd: Not a directory or not exists: " << directoryPath << std::endl;
        return nullptr;
      }
      currentDirectory = std::dynamic_pointer_cast<Directory>(child);
    }
  }

  return currentDirectory;
}

std::shared_ptr<Directory>
FileSystem::resolveParentDirectory(const std::string &path,
                                   std::string &componentName) const {
  if (path.empty()) {
    return nullptr;
  }

  auto lastSlash = path.rfind(PATH_SEPARATOR_CHAR);
  if (lastSlash == std::string::npos) {
    componentName = path;
    return currentWorkingDirectory;
  }

  componentName = path.substr(lastSlash + 1);
  auto parentPath = path.substr(0, lastSlash);
  return parentPath.empty() ? rootDirectory : resolveDirectory(parentPath);
}

std::shared_ptr<File>
FileSystem::resolveFile(const std::string &filePath) const {
  std::string name;
  auto parent = resolveParentDirectory(filePath, name);

  if (!parent || name.empty()) {
    return nullptr;
  }

  auto child = parent->findChild(name);
  if (!child || child->getComponentType() != FileSystemComponentType::FILE) {
    return nullptr;
  }

  return std::dynamic_pointer_cast<File>(child);
}

bool FileSystem::createDirectory(const std::string &directoryPath) {
  std::string componentName;
  auto parent = resolveParentDirectory(directoryPath, componentName);

  if (!parent) {
    std::cout << "mkdir: No such file or directory " << directoryPath
              << std::endl;
    return false;
  }

  if (componentName.empty()) {
    return false;
  }

  if (parent->hasChild(componentName)) {
    std::cout << "mkdir: " << directoryPath << " exists" << std::endl;
    return false;
  }

  auto directory = std::make_shared<Directory>(componentName);
  directory->setParent(parent);
  parent->addChild(directory);
  save();
  return true;
}

bool FileSystem::createFile(const std::string &filePath,
                            const std::string &fileContent) {
  std::string componentName;
  auto parent = resolveParentDirectory(filePath, componentName);

  if (!parent) {
    std::cout << "touch: " << filePath << ": No such file or directory"
              << std::endl;
    return false;
  }

  if (componentName.empty()) {
    std::cout << "touch: " << filePath << ": Invalid name" << std::endl;
    return false;
  }

  auto existingChild = parent->findChild(componentName);
  if (existingChild) {
    existingChild->updateModificationTime();
  } else {
    parent->addChild(std::make_shared<File>(componentName, fileContent));
  }

  save();
  return true;
}

bool FileSystem::removeFile(const std::string &filePath) {
  std::string componentName;
  auto parent = resolveParentDirectory(filePath, componentName);

  if (!parent || !parent->hasChild(componentName)) {
    std::cout << "rm: cannot remove " << filePath << "No such file or directory"
              << std::endl;
    return false;
  }

  if (parent->findChild(componentName)->getComponentType() !=
      FileSystemComponentType::FILE) {
    std::cout << "rm: cannot remove " << componentName << " Is a directory"
              << std::endl;
    return false;
  }

  parent->removeChild(componentName);
  save();
  return true;
}

bool FileSystem::removeDirectory(const std::string &directoryPath) {
  std::string componentName;
  auto parent = resolveParentDirectory(directoryPath, componentName);

  if (!parent || !parent->hasChild(componentName)) {
    std::cout << "rm: cannot remove " << directoryPath
              << " : No such file or directory" << std::endl;
    return false;
  }

  auto child = parent->findChild(componentName);
  if (child->getComponentType() != FileSystemComponentType::DIRECTORY) {
    std::cout << "rm: cannot remove " << componentName << ": Not a directory"
              << std::endl;
    return false;
  }

  parent->removeChild(componentName);
  save();
  return true;
}

bool FileSystem::changeDirectory(const std::string &directoryPath) {
  auto target = resolveDirectory(directoryPath);
  if (!target) {
    return false;
  }
  currentWorkingDirectory = target;
  return true;
}

std::string FileSystem::getCurrentPath() const {
  std::vector<std::string> pathParts;
  auto currentDirectory = currentWorkingDirectory;

  while (currentDirectory && currentDirectory != rootDirectory) {
    pathParts.push_back(currentDirectory->getName());
    currentDirectory = currentDirectory->getParent().lock();
  }

  if (pathParts.empty()) {
    return ROOT_DIRECTORY;
  }

  std::string result;
  for (auto iterator = pathParts.rbegin(); iterator != pathParts.rend();
       iterator++) {
    result += PATH_SEPARATOR + *iterator;
  }
  return result;
}
