#pragma once

#include <sstream>

#include "Direction.hpp"
#include "Position.hpp"
#include "SimulatorException.hpp"

namespace simulator {

class Robot {
public:
  Robot() : position(0, 0), direction(Direction::NORTH), isPlaced(false) {}

  bool hasPlaced() const;

  void place(Position pos, Direction dir);
  void move();
  void rotateLeft();
  void rotateRight();

  Position  getPosition() const;
  Direction getDirection() const;
  Position  calculateNextPosition() const;

private:
  Position  position;
  Direction direction;
  bool      isPlaced;
};

} // namespace simulator
