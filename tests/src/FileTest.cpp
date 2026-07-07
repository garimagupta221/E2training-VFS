#include "File.h"
#include <gtest/gtest.h>

TEST(FileTest, GettersReturnCorrectValues) {
  File file("smartPointers.txt", "Not raw pointers");
  EXPECT_EQ(file.getName(), "smartPointers.txt");
  EXPECT_EQ(file.getComponentType(), FileSystemComponentType::FILE);
  EXPECT_EQ(file.getContent(), "Not raw pointers");
  EXPECT_EQ(file.getSize(), 16);
}

TEST(FileTest, SetContentReplacesContent) {
  File file("smartPointers.txt", "garima");
  file.setContent("Not raw pointers");
  EXPECT_EQ(file.getContent(), "Not raw pointers");
  EXPECT_EQ(file.getSize(), 16);
}

TEST(FileTest, AppendContentConcatenatesContent) {
  File file("smartPointers.txt", "garima");
  file.appendContent("Not raw pointers");
  EXPECT_EQ(file.getContent(), "garimaNot raw pointers");
  EXPECT_EQ(file.getSize(), 22);
}

TEST(FileTest, SetNameUpdatesName) {
  File file("smartPointers.txt");
  file.setName("newname.txt");
  EXPECT_EQ(file.getName(), "newname.txt");
}

TEST(FileTest, SearchLinesFindsMatchingLines) {
  File file("smartPointers.txt", "first line\nsecond line\nthird match");
  auto matches = file.searchLines("line");
  EXPECT_EQ(matches[0], "first line");
  EXPECT_EQ(matches[1], "second line");
}

TEST(FileTest, SearchLinesFindsNoMatchingLines) {
  File file("smartPointers.txt", "first line\nsecond line");
  auto matches = file.searchLines("third");
  EXPECT_TRUE(matches.empty());
}
