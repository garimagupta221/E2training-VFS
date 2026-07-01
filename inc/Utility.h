#pragma once
#include <string>
#include <vector>

class Utility {
public:
  static std::vector<std::string> splitPath(const std::string &path);
  static bool isNumber(const std::string &inputString);
};
