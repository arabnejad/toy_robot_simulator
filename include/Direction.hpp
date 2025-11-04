#pragma once

#include <iostream>
#include <sstream>

namespace simulator {

enum class Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

inline std::ostream &operator<<(std::ostream &ostream, Direction dir) {
  switch (dir) {
  case Direction::NORTH:
    return ostream << "NORTH";
  case Direction::EAST:
    return ostream << "EAST";
  case Direction::SOUTH:
    return ostream << "SOUTH";
  case Direction::WEST:
    return ostream << "WEST";
  default:
    return ostream << "UNKNOWN";
  }
}

} // namespace simulator
