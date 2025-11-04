#pragma once

#include <iostream>

#include "InputReader.hpp"
namespace simulator {

class ConsoleReader : public InputReader {
public:
  std::vector<std::string> readInput() override {
    std::vector<std::string> lines;

    std::string line;
    while (std::getline(std::cin, line)) {
      if (line.empty()) {
        break;
      }
      lines.push_back(line);
    }

    return lines;
  }
};

} // namespace simulator
