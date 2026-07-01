#pragma once
#include "interfaces/IFileSystemComponent.h"
#include <string>
#include <vector>

class File : public IFileSystemComponent {
public:
  explicit File(const std::string &name, const std::string &content = "");

  std::string getName() const override;
  std::size_t getSize() const override;
  FileSystemComponentType getComponentType() const override;
  std::time_t getCreationTime() const override;
  std::time_t getModificationTime() const override;
  void setName(const std::string &name) override;
  void updateModificationTime() override;

  std::string getContent() const;
  void setContent(const std::string &content);
  void appendContent(const std::string &content);
  std::vector<std::string> searchLines(const std::string &pattern) const;

private:
  std::string name;
  std::string content;
  std::time_t creationTime;
  std::time_t modificationTime;
};
