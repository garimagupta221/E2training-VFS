#include "Directory.h"
#include "MockFileSystemComponent.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;

class DirectoryTest : public ::testing::Test {
protected:
  std::shared_ptr<Directory> root;
  void SetUp() override { root = std::make_shared<Directory>("root"); }
};

TEST_F(DirectoryTest, GettersReturnCorrectValues) {
  EXPECT_EQ(root->getName(), "root");
  EXPECT_EQ(root->getComponentType(), FileSystemComponentType::DIRECTORY);
}

TEST_F(DirectoryTest, AddDirectoryChild) {
  auto child = std::make_shared<Directory>("docs");
  root->addChild(child);
  EXPECT_TRUE(root->hasChild("docs"));
}

TEST_F(DirectoryTest, AddMockFileChild) {
  auto mockFile = std::make_shared<MockFileSystemComponent>();
  EXPECT_CALL(*mockFile, getName()).WillRepeatedly(Return("printers.txt"));
  EXPECT_CALL(*mockFile, getComponentType())
      .WillRepeatedly(Return(FileSystemComponentType::FILE));
  root->addChild(mockFile);
  EXPECT_TRUE(root->hasChild("printers.txt"));
}

TEST_F(DirectoryTest, HasChildReturnsFalseForMissingChild) {
  EXPECT_FALSE(root->hasChild("garima.txt"));
}

TEST_F(DirectoryTest, RemoveChildRemovesCorrectMock) {
  auto child1 = std::make_shared<MockFileSystemComponent>();
  EXPECT_CALL(*child1, getName()).WillRepeatedly(Return("docs"));

  auto child2 = std::make_shared<MockFileSystemComponent>();
  EXPECT_CALL(*child2, getName()).WillRepeatedly(Return("Downloads"));

  root->addChild(child1);
  root->addChild(child2);
  EXPECT_TRUE(root->hasChild("docs"));
  EXPECT_TRUE(root->hasChild("Downloads"));
  root->removeChild("docs");
  EXPECT_FALSE(root->hasChild("docs"));
  EXPECT_TRUE(root->hasChild("Downloads"));
}

TEST_F(DirectoryTest, GetChildrenReturnsAllChildren) {
  auto child1 = std::make_shared<Directory>("dir1");
  auto child2 = std::make_shared<Directory>("dir2");
  root->addChild(child1);
  root->addChild(child2);
  EXPECT_EQ(root->getChildren().size(), 2);
}

TEST_F(DirectoryTest, DoNotAddDuplicateChild) {
  auto child1 = std::make_shared<Directory>("dir1");
  auto child2 = std::make_shared<Directory>("dir1");
  root->addChild(child1);
  root->addChild(child2);
  EXPECT_EQ(root->getChildren().size(), 1);
}

TEST_F(DirectoryTest, GetSizeSumsMockFileChildrenSizes) {
  auto child1 = std::make_shared<MockFileSystemComponent>();
  auto child2 = std::make_shared<MockFileSystemComponent>();
  EXPECT_CALL(*child1, getName()).WillRepeatedly(Return("file1"));
  EXPECT_CALL(*child2, getName()).WillRepeatedly(Return("file2"));
  EXPECT_CALL(*child1, getSize()).WillRepeatedly(Return(13));
  EXPECT_CALL(*child2, getSize()).WillRepeatedly(Return(22));

  root->addChild(child1);
  root->addChild(child2);
  EXPECT_EQ(root->getSize(), 35);
}

TEST_F(DirectoryTest, SetNameUpdatesName) {
  root->setName("documents");
  EXPECT_EQ(root->getName(), "documents");
}

TEST_F(DirectoryTest, SetParentReturnsCorrectParent) {
  auto dir1 = std::make_shared<Directory>("parent");
  auto dir2 = std::make_shared<Directory>("child");
  dir2->setParent(dir1);
  EXPECT_EQ(dir2->getParent().lock()->getName(), "parent");
}