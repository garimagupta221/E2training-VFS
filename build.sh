mkdir -p bin

g++ -Iinc -Iinc/commands -Itests/inc -Itests/src tests/src/main.cpp tests/src/CommandProcessorTest.cpp tests/src/DirectoryTest.cpp tests/src/FileSystemTest.cpp tests/src/FileTest.cpp tests/src/UtilityTest.cpp src/Application.cpp src/CommandProcessor.cpp src/ConcreteCommandFactory.cpp src/Directory.cpp src/File.cpp src/FileSystem.cpp src/FileSystemPersistence.cpp src/Utility.cpp src/commands/CatCommand.cpp src/commands/CdCommand.cpp src/commands/EchoCommand.cpp src/commands/FindCommand.cpp src/commands/HelpCommand.cpp src/commands/LsCommand.cpp src/commands/MkdirCommand.cpp src/commands/PwdCommand.cpp src/commands/RmCommand.cpp src/commands/TouchCommand.cpp -lgtest -lgmock -o bin/AllTests
./bin/AllTests

g++ -Iinc -Iinc/commands src/*.cpp src/commands/*.cpp -o bin/vfs
./bin/vfs
