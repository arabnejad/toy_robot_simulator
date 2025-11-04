#pragma once

#include <memory>
#include <sstream>

#include "Logger.hpp"
#include "Robot.hpp"
#include "SimulatorGround.hpp"
#include "utils.hpp"

namespace simulator {

// Abstract base class for all commands
class Command {
public:
  virtual ~Command() = default;

  virtual void execute(Robot &robot, SimulatorGround &ground) = 0;
};

class PlaceCommand : public Command {
public:
  PlaceCommand(Position pos, Direction dir) : position(pos), direction(dir), logger(Logger::getInstance()) {}

  void execute(Robot &robot, SimulatorGround &ground) override;

private:
  Position  position;
  Direction direction;
  Logger   &logger;
};

class MoveCommand : public Command {
public:
  MoveCommand() : logger(Logger::getInstance()) {}

  void execute(Robot &robot, SimulatorGround &ground) override;

private:
  Logger &logger;
};

class LeftCommand : public Command {
public:
  LeftCommand() : logger(Logger::getInstance()) {}

  void execute(Robot &robot, SimulatorGround &ground) override;

private:
  Logger &logger;
};

class RightCommand : public Command {
public:
  RightCommand() : logger(Logger::getInstance()) {}

  void execute(Robot &robot, SimulatorGround &ground) override;

private:
  Logger &logger;
};

class ReportCommand : public Command {
public:
  ReportCommand() : logger(Logger::getInstance()) {}

  void execute(Robot &robot, SimulatorGround &ground) override;

private:
  Logger &logger;
};
} // namespace simulator
