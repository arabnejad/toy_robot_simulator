#include <iostream>
#include <memory>

#include "ArgParser.hpp"
#include "CommandFactory.hpp"
#include "ConsoleReader.hpp"
#include "FileReader.hpp"
#include "InputReader.hpp"
#include "Logger.hpp"
#include "RobotSimulator.hpp"
#include "SimulatorException.hpp"

int main(int argc, char *argv[]) {
  try {
    simulator::ArgParser argParser(argc, argv);
    argParser.parse();

    if (argParser.showHelpMessage()) {
      simulator::ArgParser::printHelp();
      return 0;
    }

    // Configure logger
    simulator::Logger &logger = simulator::Logger::getInstance();
    logger.setLogLevel(argParser.getLogLevel());

    logger.info("Simulator started");
    logger.debug("Log level set to: " + logger.getLogLevelAsString());

    // Create reader based on input arguments
    std::unique_ptr<simulator::InputReader> reader;

    if (argParser.hasInputFile()) {
      std::string filepath = argParser.getInputFile();
      logger.info("Reading from file: " + filepath);
      reader = std::make_unique<simulator::FileReader>(filepath);
    } else {
      std::cout << "Enter lines (empty line to finish):\n";
      reader = std::make_unique<simulator::ConsoleReader>();
    }

    auto commandFactory = std::make_unique<simulator::CommandFactory>();
    auto ground         = std::make_unique<simulator::SimulatorGround>(5, 5);

    // Create Robot simulator and pass reader ownership
    simulator::RobotSimulator robotSimulator(std::move(reader), std::move(commandFactory), std::move(ground));

    // Run the simulation
    robotSimulator.run();

  } catch (const simulator::InvalidInputException &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  } catch (const simulator::FileException &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  } catch (const simulator::SimulatorException &e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  } catch (const std::exception &e) {
    std::cerr << "Unexpected error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
