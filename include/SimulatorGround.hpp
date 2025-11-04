#pragma once

#include "Position.hpp"
#include "SimulatorException.hpp"

namespace simulator {

class SimulatorGround {
public:
  SimulatorGround(int rows, int cols) : maxRows(rows), maxCols(cols) {

    if (rows <= 0 || cols <= 0) {
      throw InvalidInputException("Simulator Ground dimensions must be positive");
    }
  }

  bool isValidPosition(const Position &pos) const {
    return pos.x >= 0 && pos.x < maxCols && pos.y >= 0 && pos.y < maxRows;
  }

  int getRows() const {
    return maxRows;
  }

  int getCols() const {
    return maxCols;
  }

private:
  int maxRows;
  int maxCols;
};

} // namespace simulator
