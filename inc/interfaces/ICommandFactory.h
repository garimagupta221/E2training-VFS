
#pragma once
#include "ICommand.h"
#include <memory>
#include <string>

class ICommandFactory {
public:
  virtual ~ICommandFactory() = default;
  virtual std::unique_ptr<ICommand>
  createCommand(const std::string &commandName) = 0;
};
