#include "Utility.h"
#include "VFSConstants.h"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>

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

std::optional<std::time_t> Utility::parseDate(const std::string &dateString,
                                              bool isEndOfDay) {
  std::tm calendarDate = {};
  std::istringstream inputStream(dateString);
  inputStream >> std::get_time(&calendarDate, "%Y-%m-%d");

  if (inputStream.fail()) {
    return std::nullopt;
  }

  calendarDate.tm_hour = isEndOfDay ? 23 : 0;
  calendarDate.tm_min  = isEndOfDay ? 59 : 0;
  calendarDate.tm_sec  = isEndOfDay ? 59 : 0;
  calendarDate.tm_isdst = -1;

  std::time_t parsedTime = std::mktime(&calendarDate);
  if (parsedTime == -1) {
    return std::nullopt;
  }
  return parsedTime;
}
