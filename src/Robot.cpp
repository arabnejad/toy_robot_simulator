

#include "Robot.hpp"
namespace simulator {

void Robot::place(Position pos, Direction dir) {
  position  = pos;
  direction = dir;
  isPlaced  = true;
}

bool Robot::hasPlaced() const {
  return isPlaced;
}

Position Robot::getPosition() const {
  if (!isPlaced) {
    throw InvalidInputException("Robot has not been placed yet");
  }
  return position;
}

Direction Robot::getDirection() const {
  if (!isPlaced) {
    throw InvalidInputException("Robot has not been placed yet");
  }
  return direction;
}

void Robot::move() {
  if (!isPlaced) {
    throw InvalidInputException("Robot must be placed before moving");
  }

  switch (direction) {
  case Direction::NORTH:
    position.y++;
    break;
  case Direction::SOUTH:
    position.y--;
    break;
  case Direction::EAST:
    position.x++;
    break;
  case Direction::WEST:
    position.x--;
    break;
  }
}

Position Robot::calculateNextPosition() const {
  if (!isPlaced) {
    throw InvalidInputException("Robot must be placed before calculating the next position");
  }

  Position next = position;

  switch (direction) {
  case Direction::NORTH:
    next.y++;
    break;
  case Direction::SOUTH:
    next.y--;
    break;
  case Direction::EAST:
    next.x++;
    break;
  case Direction::WEST:
    next.x--;
    break;
  }

  return next;
}

// Rotate robot 90 degrees to the left
void Robot::rotateLeft() {
  if (!isPlaced) {
    throw InvalidInputException("Robot must be placed before rotating");
  }

  switch (direction) {
  case Direction::NORTH:
    direction = Direction::WEST;
    break;
  case Direction::WEST:
    direction = Direction::SOUTH;
    break;
  case Direction::SOUTH:
    direction = Direction::EAST;
    break;
  case Direction::EAST:
    direction = Direction::NORTH;
    break;
  }
}

// Rotate robot 90 degrees to the right
void Robot::rotateRight() {
  if (!isPlaced) {
    throw InvalidInputException("Robot must be placed before rotating");
  }

  switch (direction) {
  case Direction::NORTH:
    direction = Direction::EAST;
    break;
  case Direction::EAST:
    direction = Direction::SOUTH;
    break;
  case Direction::SOUTH:
    direction = Direction::WEST;
    break;
  case Direction::WEST:
    direction = Direction::NORTH;
    break;
  }
}

} // namespace simulator
