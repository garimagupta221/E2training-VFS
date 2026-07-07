#pragma once
#include "Directory.h"
#include "IFileSystemPersistence.h"
#include <iosfwd>
#include <string>

class FileSystemPersistence : public IFileSystemPersistence {
public:
  explicit FileSystemPersistence(const std::string &filename);

  void serialize(const FileSystem &fs) override;
  std::shared_ptr<Directory> deserialize() override;

private:
  std::string filename;

  const std::string DIR_PREFIX = "DIR:";
  const std::string FILE_PREFIX = "FILE:";
  const std::string CONTENT_PREFIX = "CONTENT:";
  const std::string END_FILE_TAG = "END_FILE";

  bool hasPrefix(const std::string &str, const std::string &prefix) const;
  std::string removePrefix(const std::string &line,
                           const std::string &prefix) const;
  void saveDirectory(std::ofstream &outFile,
                     const std::shared_ptr<Directory> &dir,
                     const std::string &currentPath) const;
  void deserializeDirectory(const std::string &directoryPath,
                            const std::shared_ptr<Directory> &root) const;
  std::string readFileContent(std::ifstream &file,
                              std::size_t contentSize) const;
  std::shared_ptr<Directory>
  ensureParentDir(const std::shared_ptr<Directory> &root,
                  const std::string &path, std::string &childName) const;
};
