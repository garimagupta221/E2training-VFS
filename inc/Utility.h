#pragma once
#include <optional>
#include <ctime>
#include <string>
#include <vector>

class Utility {
public:
  static std::vector<std::string> splitPath(const std::string &path);
  static bool isNumber(const std::string &inputString);
  static std::optional<std::time_t> parseDate(const std::string &dateString, bool isEndOfDay);
};
