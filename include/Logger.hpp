#pragma once

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace simulator {

enum class LogLevel {
  NONE    = 0,
  ERROR   = 1,
  WARNING = 2,
  INFO    = 3,
  DEBUG   = 4,
  TRACE   = 5
};

inline std::ostream &operator<<(std::ostream &ostream, LogLevel level) {
  switch (level) {
  case LogLevel::NONE:
    return ostream << "NONE";
  case LogLevel::ERROR:
    return ostream << "ERROR";
  case LogLevel::WARNING:
    return ostream << "WARNING";
  case LogLevel::INFO:
    return ostream << "INFO";
  case LogLevel::DEBUG:
    return ostream << "DEBUG";
  case LogLevel::TRACE:
    return ostream << "TRACE";
  default:
    return ostream << "UNKNOWN";
  }
}

class Logger {
public:
  static Logger &getInstance() {
    static Logger instance;
    return instance;
  }

  // Delete copy constructor and assignment operator (Rule of Five)
  Logger(const Logger &)            = delete;
  Logger &operator=(const Logger &) = delete;
  Logger(Logger &&)                 = delete;
  Logger &operator=(Logger &&)      = delete;

  void setLogLevel(LogLevel level) {
    currentLevel = level;
  }

  LogLevel getLogLevel() const {
    return currentLevel;
  }

  std::string getLogLevelAsString() const {
    std::ostringstream oss;
    oss << currentLevel;
    return oss.str();
  }

  void log(LogLevel level, const std::string &message) {
    // Check if logging is disabled or level is too low
    if (currentLevel == LogLevel::NONE || level > currentLevel) {
      return;
    }

    std::string logMessage = formatLogMessage(level, message);

    std::cout << logMessage << std::endl;
  }

  void error(const std::string &message) {
    log(LogLevel::ERROR, message);
  }

  void warning(const std::string &message) {
    log(LogLevel::WARNING, message);
  }

  void info(const std::string &message) {
    log(LogLevel::INFO, message);
  }

  void debug(const std::string &message) {
    log(LogLevel::DEBUG, message);
  }

  void trace(const std::string &message) {
    log(LogLevel::TRACE, message);
  }

  ~Logger() {}

private:
  Logger() : currentLevel(LogLevel::INFO) {}

  std::string formatLogMessage(LogLevel level, const std::string &message) {
    std::ostringstream oss;

    // Add timestamp
    std::time_t now      = std::time(nullptr);
    std::tm    *timeinfo = std::localtime(&now);
    char        timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    oss << "[" << timestamp << "] " << "[" << std::left << std::setw(7) << level << "] " << message;
    // oss << "[" << timestamp << "] " << "[" << level << "] " << message;

    return oss.str();
  }

  LogLevel currentLevel;
};

} // namespace simulator
