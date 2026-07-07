cmake_minimum_required(VERSION 3.14)
project(VFS CXX)

set(CMAKE_CXX_STANDARD 17)       
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(GTest REQUIRED)
include_directories(
    inc
    inc/commands
    tests/inc
)

add_library(vfs_lib STATIC
    src/FileSystem.cpp
    src/Directory.cpp
    src/File.cpp
    src/Utility.cpp
    src/FileSystemPersistence.cpp
    src/CommandProcessor.cpp
    src/ConcreteCommandFactory.cpp
    src/Application.cpp
    src/commands/CatCommand.cpp
    src/commands/CdCommand.cpp
    src/commands/EchoCommand.cpp
    src/commands/FindCommand.cpp
    src/commands/HelpCommand.cpp
    src/commands/LsCommand.cpp
    src/commands/MkdirCommand.cpp
    src/commands/PwdCommand.cpp
    src/commands/RmCommand.cpp
    src/commands/TouchCommand.cpp
)

add_executable(vfs src/main.cpp)
target_link_libraries(vfs PRIVATE vfs_lib)

enable_testing()

# === Helper function to define test targets ===
function(add_vfs_test target_name)
    add_executable(${target_name} ${ARGN})
    target_link_libraries(${target_name}
        vfs_lib
        GTest::gtest_main
        GTest::gmock
    )
    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction()

add_vfs_test(UtilityTest tests/src/UtilityTest.cpp)
add_vfs_test(FileTest tests/src/FileTest.cpp)
add_vfs_test(DirectoryTest tests/src/DirectoryTest.cpp)
add_vfs_test(FileSystemTest tests/src/FileSystemTest.cpp)
add_vfs_test(CommandProcessorTest tests/src/CommandProcessorTest.cpp)
