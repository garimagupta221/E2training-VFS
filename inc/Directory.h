
#pragma once
#include "IFileSystemComponent.h"
#include <memory>
#include <vector>


class Directory : public IFileSystemComponent {
public:
  explicit Directory(const std::string &name);

  std::string getName() const override;
  std::size_t getSize() const override;
  FileSystemComponentType getComponentType() const override;
  std::time_t getCreationTime() const override;
  std::time_t getModificationTime() const override;
  void setName(const std::string &name) override;
  void updateModificationTime() override;

  std::weak_ptr<Directory> getParent() const;
  void setParent(std::weak_ptr<Directory> parent);

  void addChild(std::shared_ptr<IFileSystemComponent> component);
  void removeChild(const std::string &childName);
  bool hasChild(const std::string &childName) const;

  std::vector<std::shared_ptr<IFileSystemComponent>> getChildren() const;
  std::shared_ptr<IFileSystemComponent>
  findChild(const std::string &childName) const;

private:
  std::string name;
  std::time_t creationTime;
  std::time_t modificationTime;
  std::vector<std::shared_ptr<IFileSystemComponent>> children;
  std::weak_ptr<Directory> parent;
};
