#include "Utility.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(UtilityTest, SplitPathAbsoluteGiveValidParts) {
  std::vector<std::string> parts = Utility::splitPath("/home/user/documents");
  EXPECT_EQ(parts[0], "home");
  EXPECT_EQ(parts[1], "user");
  EXPECT_EQ(parts[2], "documents");
}

TEST(UtilityTest, SplitPathRelativeGiveValidParts) {
  auto parts = Utility::splitPath("home/user");
  EXPECT_EQ(parts[0], "home");
  EXPECT_EQ(parts[1], "user");
}

TEST(UtilityTest, SplitPathEmptyStringGiveEmptyParts) {
  auto parts = Utility::splitPath("");
  EXPECT_TRUE(parts.empty());
}

TEST(UtilityTest, SplitPathSingleDirectoryGiveValidParts) {
  auto parts = Utility::splitPath("docs");
  EXPECT_EQ(parts[0], "docs");
}

TEST(UtilityTest, SplitPathTrailingSlashGiveValidParts) {
  auto parts = Utility::splitPath("home/user/");
  EXPECT_EQ(parts[0], "home");
  EXPECT_EQ(parts[1], "user");
}

TEST(UtilityTest, SplitPathMultipleSeparators) {
  auto parts = Utility::splitPath("//home///user//");
  EXPECT_EQ(parts[0], "home");
  EXPECT_EQ(parts[1], "user");
}

TEST(UtilityTest, IsNumberPositiveInteger) {
  EXPECT_TRUE(Utility::isNumber("4278"));
  EXPECT_TRUE(Utility::isNumber("0"));
}

TEST(UtilityTest, IsNumberNegativeNotAllowed) {
  EXPECT_FALSE(Utility::isNumber("-1"));
}

TEST(UtilityTest, IsNumberEmptyString) { EXPECT_FALSE(Utility::isNumber("")); }

TEST(UtilityTest, IsNumberContainsAlphabet) {
  EXPECT_FALSE(Utility::isNumber("garia"));
  EXPECT_FALSE(Utility::isNumber("4512garia"));
}

TEST(UtilityTest, GetParseDateValidDate) {
  auto result = Utility::parseDate("2025-06-20", false);
  EXPECT_TRUE(result.has_value());
}

TEST(UtilityTest, GetParseDateInvalidDate) {
  auto result = Utility::parseDate("15-06-2025", false);
  EXPECT_FALSE(result.has_value());
}