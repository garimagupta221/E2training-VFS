#include "Utility.h"
#include "VFSConstants.h"
#include <algorithm>
#include <cctype>

std::vector<std::string> Utility::splitPath(const std::string &path) {
  std::vector<std::string> parts;
  std::string part;
  for (char character : path) {
    if (character == PATH_SEPARATOR_CHAR) {
      if (!part.empty()) {
        parts.push_back(part);
      }
      part.clear();
    } else {
      part += character;
    }
  }
  if (!part.empty()) {
    parts.push_back(part);
  }
  return parts;
}

bool Utility::isNumber(const std::string &inputString) {
  return inputString.empty() == false &&
         std::all_of(inputString.begin(), inputString.end(),
                     [](char character) { return std::isdigit(character); });
}
