
#pragma once
#include <ctime>
#include <string>

enum class FileSystemComponentType { FILE, DIRECTORY };

class IFileSystemComponent {
public:
  virtual ~IFileSystemComponent() = default;

  virtual std::string getName() const = 0;
  virtual std::size_t getSize() const = 0;
  virtual FileSystemComponentType getComponentType() const = 0;
  virtual std::time_t getCreationTime() const = 0;
  virtual std::time_t getModificationTime() const = 0;
  virtual void setName(const std::string &name) = 0;
  virtual void updateModificationTime() = 0;
};
