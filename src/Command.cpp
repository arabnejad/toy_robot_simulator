
#include "Command.hpp"

namespace simulator {

void PlaceCommand::execute(Robot &robot, SimulatorGround &ground) {
  if (!ground.isValidPosition(position)) {
    std::ostringstream oss;
    oss << "Cannot PLACE robot at " << position << ": position out of bounds (ground is " << ground.getCols() << "x"
        << ground.getRows() << ")";
    throw InvalidInputException(oss.str());
  }

  // Execute PLACE command
  robot.place(position, direction);

  {
    std::ostringstream oss;
    oss << "robot placed at " << position << " facing " << direction;
    logger.info(oss.str());
  }
}

void MoveCommand::execute(Robot &robot, SimulatorGround &ground) {

  if (!robot.hasPlaced()) {
    throw InvalidInputException("Robot must be placed before MOVE command");
  }

  Position nextPosition = robot.calculateNextPosition();

  if (!ground.isValidPosition(nextPosition)) {
    std::ostringstream oss;
    oss << "Cannot move to " << nextPosition << ": position out of bounds";
    throw InvalidInputException(oss.str());
  }

  // Execute MOVE command
  robot.move();

  {
    std::ostringstream oss;
    oss << "Robot moved to " << nextPosition << " facing " << robot.getDirection();
    logger.info(oss.str());
  }
}

void LeftCommand::execute(Robot &robot, SimulatorGround &ground) {
  UNUSED(ground); // Suppress warning: unused parameter ‘ground’

  if (!robot.hasPlaced()) {
    throw InvalidInputException("Robot must be placed before LEFT command");
  }

  // Execute LEFT command
  robot.rotateLeft();

  {
    std::ostringstream oss;
    oss << "Robot rotated LEFT, now facing " << robot.getDirection();
    logger.info(oss.str());
  }
}

void RightCommand::execute(Robot &robot, SimulatorGround &ground) {
  UNUSED(ground); // Suppress warning: unused parameter ‘ground’

  if (!robot.hasPlaced()) {
    throw InvalidInputException("Robot must be placed before RIGHT command");
  }

  // Execute RIGHT command
  robot.rotateRight();

  {
    std::ostringstream oss;
    oss << "Robot rotated RIGHT, now facing " << robot.getDirection();
    logger.info(oss.str());
  }
}

void ReportCommand::execute(Robot &robot, SimulatorGround &ground) {
  UNUSED(ground); // Suppress warning: unused parameter ‘ground’

  if (!robot.hasPlaced()) {
    Logger::getInstance().warning("REPORT command called but robot has not placed");
    return;
  }

  // Execute REPORT command
  Position  pos = robot.getPosition();
  Direction dir = robot.getDirection();
  std::cout << "Output: " << pos << "," << dir << std::endl;
}

} // namespace simulator
