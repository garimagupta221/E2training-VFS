#include "HelpCommand.h"
#include <iostream>
#include <unordered_map>

HelpCommand::HelpCommand(FileSystem &fileSystem) : fileSystem(fileSystem) {}

void HelpCommand::execute(const std::vector<std::string> &arguments) {
  if (arguments.size() < 2) {
    showHelp();
  } else {
    showCommandHelp(arguments[1]);
  }
}

void HelpCommand::showHelp() const {
  std::cout << "  cat <file...>         - Display file contents" << std::endl;
  std::cout << "  cd [path]             - Change directory" << std::endl;
  std::cout << "  echo <text...>        - Display text" << std::endl;
  std::cout << "  find <path> [options] - Find files/directories" << std::endl;
  std::cout << "  help [command]        - Show help" << std::endl;
  std::cout << "  ls [path]             - List directory contents" << std::endl;
  std::cout << "  mkdir <dir...>        - Create directories" << std::endl;
  std::cout << "  pwd                   - Show current directory" << std::endl;
  std::cout << "  rm <file...>          - Remove files" << std::endl;
  std::cout << "  rm -r <dir>           - Remove directory" << std::endl;
  std::cout << "  touch <file...>       - Create empty files" << std::endl;
}

void HelpCommand::showCommandHelp(const std::string &command) const {
  const std::unordered_map<std::string, std::string> helpTexts = {
      {"cat", "cat <file...> - Display the contents of one or more files"},
      {"cd",
       "cd [path] - Change current directory. If no path given, goes to root"},
      {"echo", "echo <text...> [> file] | [>> file] - Display the provided "
               "text, redirecting to overwrite or append to a file"},
      {"find",
       "find <path> [options...] - Find files/directories. Options:\n"
       "  -name <pattern>           - Find by name\n"
       "  -content <text>          - Find files containing text\n"
       "  -size <min> <max>         - Find by size range in bytes\n"
       "  -timestamp <start> <end>  - Find by date range (format: YYYY-MM-DD)\n"
       "                              e.g. find . -timestamp 2025-07-01 2025-07-05"},
      {"help",
       "help [command] - Show general help or help for specific command"},
      {"ls", "ls [path] - List contents of directory. If no path given, lists "
             "current directory"},
      {"mkdir", "mkdir <dirname...> - Create one or more new directories"},
      {"pwd", "pwd - Display current working directory path"},
      {"rm", "rm <file...> - Remove one or more files\n"
             "rm -r <dir>  - Remove a directory"},
      {"touch", "touch <filename...> - Create one or more new empty files"}};

  auto iterator = helpTexts.find(command);
  if (iterator != helpTexts.end()) {
    std::cout << iterator->second << std::endl;
  } else {
    std::cout << "No help available for command: " << command << std::endl;
  }
}
