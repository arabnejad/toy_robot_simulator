#pragma once

#include <fstream>

#include "InputReader.hpp"
#include "SimulatorException.hpp"

namespace simulator {
class FileReader : public InputReader {

public:
  explicit FileReader(const std::string path) : filepath(path) {}

  std::vector<std::string> readInput() override {
    std::vector<std::string> lines;

    std::ifstream file(filepath);
    if (!file.is_open()) {
      throw simulator::FileException(filepath);
    }

    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }

    file.close();
    return lines;
  }

private:
  std::string filepath;
};

} // namespace simulator
