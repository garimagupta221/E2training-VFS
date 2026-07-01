
#include "FileSystemPersistence.h"
#include "Directory.h"
#include "File.h"
#include "FileSystem.h"
#include "Utility.h"
#include "VFSConstants.h"
#include <fstream>

FileSystemPersistence::FileSystemPersistence(const std::string &filename)
    : filename(filename) {}

void FileSystemPersistence::serialize(const FileSystem &fileSystem) {
  std::ofstream outFile(filename);
  if (outFile.is_open() == false) {
    return;
  }

  auto root = fileSystem.getRootDirectory();
  if (root != nullptr) {
    saveDirectory(outFile, root, ROOT_DIRECTORY);
  }
}

std::shared_ptr<Directory> FileSystemPersistence::deserialize() {
  std::ifstream file(filename);
  if (file.is_open() == false) {
    return nullptr;
  }

  auto root = std::make_shared<Directory>(ROOT_DIRECTORY);

  std::string line;
  while (std::getline(file, line)) {

    if (line.empty()) {
      continue;
    }

    if (hasPrefix(line, DIR_PREFIX)) {
      auto directoryPath = removePrefix(line, DIR_PREFIX);
      deserializeDirectory(directoryPath, root);
    } else if (hasPrefix(line, FILE_PREFIX)) {
      auto filePath = removePrefix(line, FILE_PREFIX);

      if (std::getline(file, line) && hasPrefix(line, CONTENT_PREFIX)) {
        auto contentSize = std::stoull(removePrefix(line, CONTENT_PREFIX));
        auto content = readFileContent(file, contentSize);

        std::string name;
        auto parent = ensureParentDir(root, filePath, name);
        if (parent && !parent->hasChild(name)) {
          auto fileNode = std::make_shared<File>(name, content);
          parent->addChild(fileNode);
        }
      }
    }
  }
  return root;
}

void FileSystemPersistence::saveDirectory(
    std::ofstream &outFile, const std::shared_ptr<Directory> &dir,
    const std::string &currentPath) const {

  const auto &children = dir->getChildren();
  for (const auto &child : children) {

    std::string childPath =
        (currentPath == ROOT_DIRECTORY)
            ? ROOT_DIRECTORY + child->getName()
            : currentPath + PATH_SEPARATOR + child->getName();
    if (child->getComponentType() == FileSystemComponentType::DIRECTORY) {
      outFile << DIR_PREFIX << childPath << std::endl;
      saveDirectory(outFile, std::dynamic_pointer_cast<Directory>(child),
                    childPath);
    } else {
      auto fileNode = std::dynamic_pointer_cast<File>(child);
      const std::string &content = fileNode->getContent();
      outFile << FILE_PREFIX << childPath << std::endl;
      outFile << CONTENT_PREFIX << content.size() << std::endl;
      if (content.size() > 0) {
        outFile << content << std::endl;
      }
      outFile << END_FILE_TAG << std::endl;
    }
  }
}

bool FileSystemPersistence::hasPrefix(const std::string &inputString,
                                      const std::string &prefix) const {
  return (inputString.size() >= prefix.size() &&
          inputString.compare(0, prefix.size(), prefix) == 0);
}

std::string
FileSystemPersistence::removePrefix(const std::string &inputString,
                                    const std::string &prefix) const {
  return inputString.substr(prefix.size());
}

std::shared_ptr<Directory>
FileSystemPersistence::ensureParentDir(const std::shared_ptr<Directory> &root,
                                       const std::string &path,
                                       std::string &childName) const {
  std::vector<std::string> parts = Utility::splitPath(path);
  if (parts.empty()) {
    return nullptr;
  }
  childName = parts.back();
  parts.pop_back();

  auto currentDirectory = root;
  for (const auto &part : parts) {
    auto child = currentDirectory->findChild(part);
    if (!child) {
      auto newDirectory = std::make_shared<Directory>(part);
      newDirectory->setParent(currentDirectory);
      currentDirectory->addChild(newDirectory);
      currentDirectory = newDirectory;
    } else if (child->getComponentType() ==
               FileSystemComponentType::DIRECTORY) {
      currentDirectory = std::dynamic_pointer_cast<Directory>(child);
    } else {
      return nullptr;
    }
  }
  return currentDirectory;
}

void FileSystemPersistence::deserializeDirectory(
    const std::string &directoryPath,
    const std::shared_ptr<Directory> &root) const {
  std::string name;
  auto parent = ensureParentDir(root, directoryPath, name);
  if (parent && !parent->hasChild(name)) {
    auto dir = std::make_shared<Directory>(name);
    dir->setParent(parent);
    parent->addChild(dir);
  }
}

std::string
FileSystemPersistence::readFileContent(std::ifstream &file,
                                       std::size_t contentSize) const {
  if (contentSize == 0) {
    return "";
  }
  std::string content(contentSize, '\0');
  std::streamsize size = contentSize;
  file.read(content.data(), size);

  std::string line;
  std::getline(file, line);

  return content;
}
