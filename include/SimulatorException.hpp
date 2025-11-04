#pragma once

#include <exception>
#include <string>

namespace simulator {

class SimulatorException : public std::exception {
public:
  explicit SimulatorException(const std::string &message) : error_message(message) {}

  const char *what() const noexcept override {
    return error_message.c_str();
  }

  virtual ~SimulatorException() = default;

private:
  std::string error_message;
};

class FileException : public SimulatorException {
public:
  explicit FileException(const std::string &filename) : SimulatorException("Cannot open or read file: " + filename) {}
};

class ParseException : public SimulatorException {
public:
  explicit ParseException(const std::string &message) : SimulatorException("Parse error: " + message) {}

  ParseException(const std::string &message, size_t line)
    : SimulatorException("Parse error at line " + std::to_string(line) + ": " + message) {}
};

class InvalidInputException : public SimulatorException {
public:
  explicit InvalidInputException(const std::string &message) : SimulatorException("Invalid input: " + message) {}
};

} // namespace simulator
