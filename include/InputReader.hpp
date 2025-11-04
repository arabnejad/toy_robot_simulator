#pragma once

#include <string>
#include <vector>

namespace simulator {

// Abstract interface for reading inputs
class InputReader {
public:
  virtual ~InputReader() = default;

  virtual std::vector<std::string> readInput() = 0;
};
} // namespace simulator
