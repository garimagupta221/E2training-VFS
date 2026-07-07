#include "CommandProcessor.h"
#include "FileSystem.h"
#include "MockCommand.h"
#include "MockCommandFactory.h"
#include "MockFileSystemPersistence.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

using ::testing::_;
using ::testing::ByMove;
using ::testing::Return;

class CommandProcessorTest : public ::testing::Test {
protected:
  MockFileSystemPersistence mockFileSystemPersistence;
  MockCommandFactory mockCommandFactory;

  std::stringstream inputStream;
  std::streambuf *originalInputBuffer;

  void SetUp() override {
    EXPECT_CALL(mockFileSystemPersistence, deserialize())
        .WillOnce(Return(nullptr));

    originalInputBuffer = std::cin.rdbuf(inputStream.rdbuf());
  }

  void TearDown() override { std::cin.rdbuf(originalInputBuffer); }
};

TEST_F(CommandProcessorTest, ExecuteKnownCommand) {
  auto mockCommand = std::make_unique<MockCommand>();
  EXPECT_CALL(*mockCommand, execute(_)).Times(1);

  EXPECT_CALL(mockCommandFactory, createCommand("mkdir"))
      .WillOnce(Return(ByMove(std::move(mockCommand))));

  inputStream.str("mkdir docs\nexit\n");

  FileSystem fileSystem(mockFileSystemPersistence);
  fileSystem.initializeFileSystem();

  CommandProcessor processor(fileSystem, mockCommandFactory);
  processor.run();
}

TEST_F(CommandProcessorTest, UnknownCommand) {
  EXPECT_CALL(mockCommandFactory, createCommand("remove"))
      .WillOnce(Return(ByMove(std::unique_ptr<ICommand>(nullptr))));

  inputStream.str("remove\nexit\n");

  FileSystem fileSystem(mockFileSystemPersistence);
  fileSystem.initializeFileSystem();

  CommandProcessor processor(fileSystem, mockCommandFactory);
  processor.run();
}

TEST_F(CommandProcessorTest, ExitCommand) {
  inputStream.str("exit\n");
  FileSystem fileSystem(mockFileSystemPersistence);
  fileSystem.initializeFileSystem();

  CommandProcessor processor(fileSystem, mockCommandFactory);
  processor.run();
}

TEST_F(CommandProcessorTest, QuitCommand) {
  inputStream.str("quit\n");

  FileSystem fileSystem(mockFileSystemPersistence);
  fileSystem.initializeFileSystem();

  CommandProcessor processor(fileSystem, mockCommandFactory);
  processor.run();
}