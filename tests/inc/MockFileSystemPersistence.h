#ifndef MOCK_FILE_SYSTEM_PERSISTENCE_H
#define MOCK_FILE_SYSTEM_PERSISTENCE_H

#include "IFileSystemPersistence.h"
#include <gmock/gmock.h>

class MockFileSystemPersistence : public IFileSystemPersistence {
public:
  MOCK_METHOD(void, serialize, (const FileSystem &filesystem), (override));
  MOCK_METHOD(std::shared_ptr<Directory>, deserialize, (), (override));
};

#endif
