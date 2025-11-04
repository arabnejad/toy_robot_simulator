#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CommandFactory.hpp"
#include "InputReader.hpp"
#include "Logger.hpp"
#include "Robot.hpp"
#include "SimulatorException.hpp"
#include "SimulatorGround.hpp"

namespace simulator {

class RobotSimulator {
public:
  explicit RobotSimulator(std::unique_ptr<InputReader> inputReader, std::unique_ptr<CommandFactory> commandParser,
                          std::unique_ptr<SimulatorGround> simulatorGround)
    : reader(std::move(inputReader))
    , parser(std::move(commandParser))
    , ground(std::move(simulatorGround))
    , logger(Logger::getInstance()) {

    if (!reader) {
      throw InvalidInputException("InputReader cannot be null");
    }

    if (!parser) {
      throw InvalidInputException("commandParser cannot be null");
    }

    if (!ground) {
      throw InvalidInputException("simulatorGround cannot be null");
    }

    logger.debug("RobotSimulator initialized with " + std::to_string(ground->getCols()) + "x" +
                 std::to_string(ground->getRows()) + " ground");
  }

  void run();

private:
  std::unique_ptr<InputReader>     reader;
  std::unique_ptr<CommandFactory>  parser;
  std::unique_ptr<SimulatorGround> ground;
  Robot                            robot;
  Logger                          &logger;
};

} // namespace simulator
