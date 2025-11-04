#pragma once

#include <algorithm>
#include <cctype>
#include <string>

#include "Logger.hpp"
#include "SimulatorException.hpp"
#include "utils.hpp"

namespace simulator {

class ArgParser {
public:
  ArgParser(int argc, char *argv[]) : argc(argc), argv(argv) {}

  // Parse command line arguments
  void parse() {
    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];

      if (arg == "--help" || arg == "-h") {
        showHelp = true;
      } else if (arg == "--file") {
        if (i + 1 < argc) {
          inputFile = argv[++i];
        } else {
          throw InvalidInputException("--file requires a filename argument");
        }
      } else if (arg.find("--loglevel") == 0) {

        size_t pos = arg.find('=');
        if (pos == std::string::npos) {
          throw InvalidInputException("--loglevel must use format: --loglevel=<LEVEL>\n"
                                      "Valid levels: NONE, ERROR, WARNING, INFO, DEBUG, TRACE");
        }

        std::string levelStr = arg.substr(pos + 1);
        if (levelStr.empty()) {
          throw InvalidInputException("--loglevel requires a value after '='");
        }

        logLevel = parseLogLevel(levelStr);

      } else {
        throw InvalidInputException("Unknown argument: " + arg + "\nUse --help for usage information");
      }
    }
  }

  bool showHelpMessage() const {
    return showHelp;
  }

  std::string getInputFile() const {
    return inputFile;
  }

  LogLevel getLogLevel() const {
    return logLevel;
  }

  bool hasInputFile() const {
    return !inputFile.empty();
  }

  static void printHelp(std::ostream &ostream = std::cout) {
    ostream << "Robot Simulator - Command Line Options\n\n"
            << "Usage: simulator [OPTIONS]\n\n"
            << "Options:\n"
            << "  --file <filename>        Specify input file to read\n"
            << "  --loglevel=<level>       Set logging level\n"
            << "                           Valid levels: NONE, ERROR, WARNING, INFO, DEBUG, TRACE\n"
            << "                           (not case sensitive)\n"
            << "  --help, -h               Display this help message\n\n"
            << "Examples:\n"
            << "  simulator --file input.txt --loglevel=DEBUG\n"
            << "  simulator --loglevel=error\n"
            << "  simulator --help\n"
            << std::endl;
  }

private:
  LogLevel parseLogLevel(const std::string &levelStr) {
    std::string upper = toUpperCase(levelStr);

    if (upper == "NONE") {
      return LogLevel::NONE;
    } else if (upper == "ERROR") {
      return LogLevel::ERROR;
    } else if (upper == "WARNING") {
      return LogLevel::WARNING;
    } else if (upper == "INFO") {
      return LogLevel::INFO;
    } else if (upper == "DEBUG") {
      return LogLevel::DEBUG;
    } else if (upper == "TRACE") {
      return LogLevel::TRACE;
    } else {
      throw InvalidInputException("Invalid log level: '" + levelStr + "'\n" +
                                  "Valid levels are: NONE, ERROR, WARNING, INFO, DEBUG, TRACE (not case sensitive)");
    }
  }

  int         argc;
  char      **argv;
  bool        showHelp = false;
  std::string inputFile;
  LogLevel    logLevel = LogLevel::NONE; // Default log level
};

} // namespace simulator
