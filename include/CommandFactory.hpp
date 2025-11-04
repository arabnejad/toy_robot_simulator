#pragma once

#include <algorithm>
#include <cctype>
#include <memory>
#include <sstream>
#include <string>

#include "Command.hpp"
#include "SimulatorException.hpp"
#include "utils.hpp"

namespace simulator {

class CommandFactory {
public:
  std::unique_ptr<Command> parse(const std::string &input);

private:
  std::unique_ptr<Command> parsePlaceCommand(const std::string &input);
  Direction                parseDirection(const std::string &direction);
};

} // namespace simulator
