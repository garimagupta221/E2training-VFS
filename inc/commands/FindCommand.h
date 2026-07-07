#pragma once
#include "Directory.h"
#include "FileSystem.h"
#include "ICommand.h"

struct SearchContext {
  const std::vector<std::string> &arguments;
  const std::vector<std::shared_ptr<IFileSystemComponent>> &components;
  std::vector<std::shared_ptr<IFileSystemComponent>> &result;
  std::time_t parsedStartTime = 0;
  std::time_t parsedEndTime = 0;
};

class FindCommand : public ICommand {
public:
  explicit FindCommand(FileSystem &fileSystem);
  void execute(const std::vector<std::string> &arguments) override;

private:
  FileSystem &fileSystem;
  void collectAllComponents(std::shared_ptr<Directory> directory,
                            std::vector<std::shared_ptr<IFileSystemComponent>>
                                &collectedComponents) const;

  void findByName(SearchContext &context) const;
  void findBySize(SearchContext &context) const;
  void findByContent(SearchContext &context) const;
  void findByTimestamp(SearchContext &context) const;

  void handleNameSearch(SearchContext &context) const;
  void handleContentSearch(SearchContext &context) const;
  void handleSizeSearch(SearchContext &context) const;
  void handleTimestampSearch(SearchContext &context) const;
};
