#include "File.h"
#include <ctime>
#include <sstream>

File::File(const std::string &name, const std::string &content)
    : name(name), content(content), creationTime(std::time(nullptr)),
      modificationTime(std::time(nullptr)) {}

std::string File::getName() const { return name; }

std::size_t File::getSize() const { return content.size(); }

std::time_t File::getCreationTime() const { return creationTime; }

std::time_t File::getModificationTime() const { return modificationTime; }

std::string File::getContent() const { return content; }

FileSystemComponentType File::getComponentType() const {
  return FileSystemComponentType::FILE;
}

void File::setName(const std::string &fileName) {
  name = fileName;
  updateModificationTime();
}

void File::updateModificationTime() { modificationTime = std::time(nullptr); }

void File::setContent(const std::string &fileContent) {
  content = fileContent;
  updateModificationTime();
}

void File::appendContent(const std::string &fileContent) {
  content += fileContent;
  updateModificationTime();
}

std::vector<std::string> File::searchLines(const std::string &pattern) const {
  std::vector<std::string> matchingLines;
  std::istringstream stream(content);
  std::string line;

  while (std::getline(stream, line)) {
    if (line.find(pattern) != std::string::npos)
      matchingLines.push_back(line);
  }
  return matchingLines;
}
