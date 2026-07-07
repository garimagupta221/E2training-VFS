#include "FindCommand.h"
#include "File.h"
#include "Utility.h"
#include <iostream>

FindCommand::FindCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void FindCommand::collectAllComponents(
    std::shared_ptr<Directory> directory,
    std::vector<std::shared_ptr<IFileSystemComponent>> &collectedComponents)
    const {
  if (directory == nullptr) {
    return;
  }
  for (const auto &child : directory->getChildren()) {
    collectedComponents.push_back(child);
    if (child->getComponentType() == FileSystemComponentType::DIRECTORY) {
      collectAllComponents(std::dynamic_pointer_cast<Directory>(child),
                           collectedComponents);
    }
  }
}

void FindCommand::findByName(SearchContext &context) const {
  for (const auto &item : context.components) {
    if (item->getName() == context.arguments[3]) {
      context.result.push_back(item);
    }
  }
}

void FindCommand::findBySize(SearchContext &context) const {
  auto minSize = std::stoul(context.arguments[3]);
  auto maxSize = std::stoul(context.arguments[4]);
  for (const auto &item : context.components) {
    auto itemSize = item->getSize();
    if (itemSize >= minSize && itemSize <= maxSize) {
      context.result.push_back(item);
    }
  }
}

void FindCommand::findByContent(SearchContext &context) const {
  for (const auto &item : context.components) {
    if (item->getComponentType() == FileSystemComponentType::FILE) {
      auto targetFile = std::dynamic_pointer_cast<File>(item);
      if (targetFile != nullptr) {
        auto matchingLines = targetFile->searchLines(context.arguments[3]);
        if (!matchingLines.empty()) {
          context.result.push_back(item);
        }
      }
    }
  }
}

void FindCommand::findByTimestamp(SearchContext &context) const {
  for (const auto &item : context.components) {
    auto itemTime = item->getModificationTime();
    if (itemTime >= context.parsedStartTime &&
        itemTime <= context.parsedEndTime) {
      context.result.push_back(item);
    }
  }
}

void FindCommand::handleNameSearch(SearchContext &context) const {
  if (context.arguments.size() < 4) {
    std::cout << "find: option requires an argument: -name" << std::endl;
    return;
  }
  if (context.arguments.size() > 4) {
    std::cout << "find: too many arguments" << std::endl;
    return;
  }
  findByName(context);
}

void FindCommand::handleContentSearch(SearchContext &context) const {
  if (context.arguments.size() < 4) {
    std::cout << "find: option requires an argument: -content" << std::endl;
    return;
  }
  if (context.arguments.size() > 4) {
    std::cout << "find: too many arguments" << std::endl;
    return;
  }
  findByContent(context);
}

void FindCommand::handleSizeSearch(SearchContext &context) const {
  if (context.arguments.size() < 5) {
    std::cout << "find: option requires two arguments: -size" << std::endl;
    return;
  }
  if (context.arguments.size() > 5) {
    std::cout << "find: too many arguments" << std::endl;
    return;
  }
  if (Utility::isNumber(context.arguments[3]) == false) {
    std::cout << "find: invalid size: '" << context.arguments[3] << "'"
              << std::endl;
    return;
  }
  if (Utility::isNumber(context.arguments[4]) == false) {
    std::cout << "find: invalid size: '" << context.arguments[4] << "'"
              << std::endl;
    return;
  }
  findBySize(context);
}

void FindCommand::handleTimestampSearch(SearchContext &context) const {
  if (context.arguments.size() < 5) {
    std::cout << "find: option requires two arguments: -timestamp" << std::endl;
    return;
  }
  if (context.arguments.size() > 5) {
    std::cout << "find: too many arguments" << std::endl;
    return;
  }
  auto startResult = Utility::parseDate(context.arguments[3], false);
  if (!startResult) {
    std::cout << "find: invalid date" << std::endl;
    return;
  }
  context.parsedStartTime = *startResult;

  auto endResult = Utility::parseDate(context.arguments[4], true);
  if (!endResult) {
    std::cout << "find: invalid date" << std::endl;
    return;
  }
  context.parsedEndTime = *endResult;
  findByTimestamp(context);
}

void FindCommand::execute(const std::vector<std::string> &arguments) {
  if (arguments.size() < 2) {
    std::cout << "find: Too few arguments" << std::endl;
    return;
  }

  const std::string &directoryPath = arguments[1];
  auto searchDirectory = fileSystem.resolveDirectory(directoryPath);
  if (searchDirectory == nullptr) {
    std::cout << "find: '" << directoryPath << "': No such file or directory"
              << std::endl;
    return;
  }

  std::vector<std::shared_ptr<IFileSystemComponent>> components;
  collectAllComponents(searchDirectory, components);

  std::vector<std::shared_ptr<IFileSystemComponent>> result;
  SearchContext context{arguments, components, result};

  if (arguments.size() == 2) {
    result = components;
  } else {
    const std::string &option = arguments[2];

    if (option == "-name") {
      handleNameSearch(context);
    } else if (option == "-content") {
      handleContentSearch(context);
    } else if (option == "-size") {
      handleSizeSearch(context);
    } else if (option == "-timestamp") {
      handleTimestampSearch(context);
    } else {
      std::cout << "find: unknown option: " << option << std::endl;
      return;
    }
  }

  if (result.empty()) {
    std::cout << "No matches found." << std::endl;
    return;
  }

  for (const auto &item : result) {
    std::cout << item->getName() << std::endl;
  }
}
