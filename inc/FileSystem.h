
#pragma once
#include "Directory.h"
#include "File.h"
#include "Utility.h"
#include "IFileSystemPersistence.h"
#include <memory>
#include <string>
#include <vector>

class FileSystem {
public:
  explicit FileSystem(IFileSystemPersistence &persistance);

  void initializeFileSystem();
  void save();

  bool createDirectory(const std::string &directoryPath);
  bool createFile(const std::string &filePath,
                  const std::string &fileContent = "");
  bool removeFile(const std::string &filePath);
  bool removeDirectory(const std::string &directoryPath);
  bool changeDirectory(const std::string &directoryPath);

  std::string getCurrentPath() const;
  std::shared_ptr<File> resolveFile(const std::string &filePath) const;
  std::shared_ptr<Directory>
  resolveDirectory(const std::string &directoryPath) const;

  std::shared_ptr<Directory> getRootDirectory() const { return rootDirectory; }
  std::shared_ptr<Directory> getCurrentWorkingDirectory() const {
    return currentWorkingDirectory;
  }

private:
  IFileSystemPersistence &persistenceProvider;
  std::shared_ptr<Directory> rootDirectory;
  std::shared_ptr<Directory> currentWorkingDirectory;
  std::shared_ptr<Directory>
  resolveParentDirectory(const std::string &path,
                         std::string &componentName) const;
};
