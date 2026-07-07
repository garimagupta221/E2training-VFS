
#include "Directory.h"
#include <algorithm>
#include <iostream>

Directory::Directory(const std::string &name)
    : name(name), creationTime(std::time(nullptr)),
      modificationTime(std::time(nullptr)) {}

std::string Directory::getName() const { return name; }

std::time_t Directory::getCreationTime() const { return creationTime; }

std::time_t Directory::getModificationTime() const { return modificationTime; }

std::weak_ptr<Directory> Directory::getParent() const { return parent; }

std::size_t Directory::getSize() const {
  std::size_t total = 0;

  for (const auto &child : children) {
    total += child->getSize();
  }

  return total;
}

FileSystemComponentType Directory::getComponentType() const {
  return FileSystemComponentType::DIRECTORY;
}

void Directory::setName(const std::string &directoryName) {
  name = directoryName;
  updateModificationTime();
}

void Directory::updateModificationTime() {
  modificationTime = std::time(nullptr);
}

void Directory::setParent(std::weak_ptr<Directory> directoryParent) {
  parent = directoryParent;
}

void Directory::addChild(std::shared_ptr<IFileSystemComponent> component) {
  if (hasChild(component->getName())) {
    std::cout << component->getName() << ": Already exists" << std::endl;
    return;
  }
  children.push_back(component);
  updateModificationTime();
}

void Directory::removeChild(const std::string &childName) {
  auto iterator = std::find_if(children.begin(), children.end(),
                               [&childName](const auto &child) {
                                 return child->getName() == childName;
                               });

  if (iterator != children.end()) {
    children.erase(iterator);
    updateModificationTime();
  }
}

bool Directory::hasChild(const std::string &childName) const {
  for (const auto &child : children) {
    if (child->getName() == childName) {
      return true;
    }
  }
  return false;
}

std::vector<std::shared_ptr<IFileSystemComponent>>
Directory::getChildren() const {
  return children;
}

std::shared_ptr<IFileSystemComponent>
Directory::findChild(const std::string &childName) const {
  for (const auto &child : children) {
    if (child->getName() == childName) {
      return child;
    }
  }
  return nullptr;
}
