#include "FileSystem.h"
#include "MockFileSystemPersistence.h"
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

class FileSystemTest : public ::testing::Test {
protected:
  MockFileSystemPersistence mockPersistence;
};

TEST_F(FileSystemTest, InitializesWithNoPersistence) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));

  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  auto root = fileSystem.getRootDirectory();
  EXPECT_EQ(root->getName(), "/");
  EXPECT_EQ(fileSystem.getCurrentPath(), "/");
}

TEST_F(FileSystemTest, InitializesWithExistingRoot) {
  auto preExistingRootDirectory = std::make_shared<Directory>("/");
  auto subDirectory = std::make_shared<Directory>("docs");
  preExistingRootDirectory->addChild(subDirectory);

  EXPECT_CALL(mockPersistence, deserialize())
      .WillOnce(Return(preExistingRootDirectory));

  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();
  auto root = fileSystem.getRootDirectory();
  EXPECT_EQ(root->getName(), "/");
  EXPECT_TRUE(root->hasChild("docs"));
}

TEST_F(FileSystemTest, CreateDirectory) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  EXPECT_CALL(mockPersistence, serialize(_)).Times(1);

  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();
  EXPECT_TRUE(fileSystem.createDirectory("docs"));
  auto root = fileSystem.getRootDirectory();
  EXPECT_TRUE(root->hasChild("docs"));
}

TEST_F(FileSystemTest, CreateDuplicateDirectoryFails) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  EXPECT_CALL(mockPersistence, serialize(_)).Times(1);
  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  EXPECT_TRUE(fileSystem.createDirectory("docs"));
  EXPECT_FALSE(fileSystem.createDirectory("docs"));
}

TEST_F(FileSystemTest, CreateDirectory_InvalidParent) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();
  EXPECT_FALSE(fileSystem.createDirectory("home/user"));
}

TEST_F(FileSystemTest, CreateFile) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  EXPECT_CALL(mockPersistence, serialize(_)).Times(1);

  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  EXPECT_TRUE(fileSystem.createFile("priyu.txt", "hi"));
  auto root = fileSystem.getRootDirectory();
  EXPECT_TRUE(root->hasChild("priyu.txt"));
  auto child = root->findChild("priyu.txt");
  ASSERT_NE(child, nullptr);
  EXPECT_EQ(child->getComponentType(), FileSystemComponentType::FILE);
}

TEST_F(FileSystemTest, RemoveFile) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  EXPECT_CALL(mockPersistence, serialize(_)).Times(2);

  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  fileSystem.createFile("priyu.txt", "hi");
  EXPECT_TRUE(fileSystem.removeFile("priyu.txt"));
  auto root = fileSystem.getRootDirectory();
  EXPECT_FALSE(root->hasChild("priyu.txt"));
}

TEST_F(FileSystemTest, RemoveFileinDirectory) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  EXPECT_CALL(mockPersistence, serialize(_)).Times(1);
  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  fileSystem.createDirectory("docs");
  EXPECT_FALSE(fileSystem.removeFile("docs"));
  auto root = fileSystem.getRootDirectory();
  EXPECT_TRUE(root->hasChild("docs"));
}

TEST_F(FileSystemTest, RemoveDirectory) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  EXPECT_CALL(mockPersistence, serialize(_)).Times(2);
  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  fileSystem.createDirectory("docs");
  EXPECT_TRUE(fileSystem.removeDirectory("docs"));
  EXPECT_EQ(fileSystem.resolveDirectory("docs"), nullptr);
}

TEST_F(FileSystemTest, ChangeDirectory) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  EXPECT_CALL(mockPersistence, serialize(_)).Times(1);

  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  fileSystem.createDirectory("docs");
  EXPECT_TRUE(fileSystem.changeDirectory("docs"));
  EXPECT_EQ(fileSystem.getCurrentPath(), "/docs");
}

TEST_F(FileSystemTest, ChangeDirectoryInvalidPath) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));

  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  EXPECT_FALSE(fileSystem.changeDirectory("GARIMA"));
}

TEST_F(FileSystemTest, GetCurrentPath) {
  EXPECT_CALL(mockPersistence, deserialize()).WillOnce(Return(nullptr));
  EXPECT_CALL(mockPersistence, serialize(_)).Times(2);

  FileSystem fileSystem(mockPersistence);
  fileSystem.initializeFileSystem();

  fileSystem.createDirectory("docs");
  fileSystem.changeDirectory("docs");
  fileSystem.createDirectory("subdirectory");
  fileSystem.changeDirectory("subdirectory");
  EXPECT_EQ(fileSystem.getCurrentPath(), "/docs/subdirectory");
}
