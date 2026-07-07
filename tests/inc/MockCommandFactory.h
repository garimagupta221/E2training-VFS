#ifndef MOCK_COMMAND_FACTORY_H
#define MOCK_COMMAND_FACTORY_H

#include "ICommandFactory.h"
#include <gmock/gmock.h>

class MockCommandFactory : public ICommandFactory {
public:
  MOCK_METHOD(std::unique_ptr<ICommand>, createCommand,
              (const std::string &commandName), (override));
};

#endif
