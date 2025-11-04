
#include "RobotSimulator.hpp"

namespace simulator {

void RobotSimulator::run() {
  logger.info("Starting Robot simulator");

  // Read input lines
  std::vector<std::string> lines = reader->readInput();

  if (lines.empty()) {
    std::cout << "No input lines to process";
    return;
  }

  logger.info("Successfully read " + std::to_string(lines.size()) + " lines");

  int errorNumber = 0;

  for (std::size_t i = 0; i < lines.size(); ++i) {
    try {
      logger.debug("Parsing command: " + lines[i]);

      // Parse command
      auto command = parser->parse(lines[i]);

      // Execute command
      command->execute(robot, *ground);

    } catch (const ParseException &e) {
      logger.error("Parse error on line " + std::to_string(i + 1) + ": " + e.what());
      errorNumber++;
    } catch (const InvalidInputException &e) {
      logger.error("Execution error on line " + std::to_string(i + 1) + ": " + e.what());
      errorNumber++;
    }
  }

  logger.info("Simulation completed with " + std::to_string(errorNumber) + " Errors.");
}

} // namespace simulator
