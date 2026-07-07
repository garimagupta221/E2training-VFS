#ifndef MOCK_FILE_SYSTEM_COMPONENT_H
#define MOCK_FILE_SYSTEM_COMPONENT_H

#include "IFileSystemComponent.h"
#include <gmock/gmock.h>

class MockFileSystemComponent : public IFileSystemComponent {
public:
  MOCK_METHOD(std::string, getName, (), (const, override));
  MOCK_METHOD(std::size_t, getSize, (), (const, override));
  MOCK_METHOD(FileSystemComponentType, getComponentType, (), (const, override));
  MOCK_METHOD(std::time_t, getCreationTime, (), (const, override));
  MOCK_METHOD(std::time_t, getModificationTime, (), (const, override));
  MOCK_METHOD(void, setName, (const std::string &name), (override));
  MOCK_METHOD(void, updateModificationTime, (), (override));
};

#endif
