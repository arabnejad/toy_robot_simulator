
#include "CommandFactory.hpp"

namespace simulator {

std::unique_ptr<Command> CommandFactory::parse(const std::string &input) {
  std::string inputCommand = trim(input);

  if (inputCommand.empty()) {
    throw ParseException("Empty command");
  }

  inputCommand = toUpperCase(inputCommand);

  if (inputCommand.find("PLACE") == 0) {
    return parsePlaceCommand(inputCommand);
  } else if (inputCommand == "MOVE") {
    return std::make_unique<MoveCommand>();
  } else if (inputCommand == "LEFT") {
    return std::make_unique<LeftCommand>();
  } else if (inputCommand == "RIGHT") {
    return std::make_unique<RightCommand>();
  } else if (inputCommand == "REPORT") {
    return std::make_unique<ReportCommand>();
  } else {
    throw ParseException("Unknown command: " + inputCommand);
  }
}

// Format: PLACE <x>,<y>,<FACE-DIRECTION>
std::unique_ptr<Command> CommandFactory::parsePlaceCommand(const std::string &input) {

  size_t spacePos = input.find(' '); // Find space after PLACE
  if (spacePos == std::string::npos) {
    throw ParseException("PLACE command requires parameters: PLACE <x>,<y>,<FACE-DIRECTION>");
  }

  std::string params = trim(input.substr(spacePos + 1));
  // Split by comma
  std::vector<std::string> tokens = split(params, ',');

  if (tokens.size() != 3) {
    throw ParseException("PLACE command requires exactly 3 parameters: x,y,direction");
  }

  int x, y;
  try {
    // Parse x and y
    x = std::stoi(trim(tokens[0]));
    y = std::stoi(trim(tokens[1]));
  } catch (const std::exception &) {
    throw ParseException("Invalid coordinates in PLACE command");
  }

  // Parse direction
  Direction dir = parseDirection(trim(tokens[2]));

  return std::make_unique<PlaceCommand>(Position(x, y), dir);
}

Direction CommandFactory::parseDirection(const std::string &direction) {
  std::string upper = toUpperCase(direction);

  if (upper == "NORTH") {
    return Direction::NORTH;
  } else if (upper == "EAST") {
    return Direction::EAST;
  } else if (upper == "SOUTH") {
    return Direction::SOUTH;
  } else if (upper == "WEST") {
    return Direction::WEST;
  } else {
    throw ParseException("Invalid direction: " + direction + ". Must be NORTH, EAST, SOUTH, or WEST");
  }
}

} // namespace simulator
