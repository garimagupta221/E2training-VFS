
#pragma once
#include "Directory.h"

class FileSystem;

class IFileSystemPersistence {
public:
  virtual ~IFileSystemPersistence() = default;
  virtual void serialize(const FileSystem &filesystem) = 0;
  virtual std::shared_ptr<Directory> deserialize() = 0;
};
