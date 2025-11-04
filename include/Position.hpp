#pragma once

#include <iostream>

namespace simulator {

struct Position {
  int x;
  int y;

  Position() : x(0), y(0) {}
  Position(int x_pos, int y_pos) : x(x_pos), y(y_pos) {}

  bool operator==(const Position &other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Position &other) const {
    return !(*this == other);
  }
};

inline std::ostream &operator<<(std::ostream &ostream, const Position &pos) {
  return ostream << pos.x << "," << pos.y;
}

} // namespace simulator
