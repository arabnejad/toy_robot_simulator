#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <vector>

#include "CommandFactory.hpp"
#include "Robot.hpp"
#include "RobotSimulator.hpp"
#include "SimulatorException.hpp"
#include "SimulatorGround.hpp"

using namespace simulator;

class MockInputReader : public InputReader {
public:
  MockInputReader(const std::vector<std::string> &test_lines) : test_lines(test_lines) {}

  std::vector<std::string> readInput() override {
    return test_lines;
  }

private:
  std::vector<std::string> test_lines;
};

class RobotSimulatorTest : public ::testing::Test {
protected:
  // https://github.com/arabnejad/cppColorLog/blob/master/tests/test_logger.cpp
  std::stringstream capturedCout;
  std::streambuf   *oldCout = nullptr;

  void SetUp() override {
    // Redirect cout to capture output
    oldCout = std::cout.rdbuf(capturedCout.rdbuf());

    // Set logger level to INFO
    Logger &logger = Logger::getInstance();
    logger.setLogLevel(LogLevel::INFO);
  }

  void TearDown() override {
    // Restore std::cout
    std::cout.rdbuf(oldCout);
  }

  std::string getCapturedOutput() {
    return capturedCout.str();
  }

  void clearOutput() {
    capturedCout.str("");
    capturedCout.clear();
  }
};

TEST_F(RobotSimulatorTest, ThrowByConstructorForNullReader) {
  auto parser = std::make_unique<CommandFactory>();
  auto ground = std::make_unique<SimulatorGround>(5, 5);

  EXPECT_THROW({ RobotSimulator sim(nullptr, std::move(parser), std::move(ground)); }, InvalidInputException);
}

TEST_F(RobotSimulatorTest, ThrowByConstructorForNullParser) {
  auto reader = std::make_unique<MockInputReader>(std::vector<std::string>());
  auto ground = std::make_unique<SimulatorGround>(5, 5);

  EXPECT_THROW({ RobotSimulator sim(std::move(reader), nullptr, std::move(ground)); }, InvalidInputException);

  EXPECT_TRUE(true);
}

TEST_F(RobotSimulatorTest, ThrowByConstructorForNullGround) {
  auto reader = std::make_unique<MockInputReader>(std::vector<std::string>());
  auto parser = std::make_unique<CommandFactory>();

  EXPECT_THROW({ RobotSimulator sim(std::move(reader), std::move(parser), nullptr); }, InvalidInputException);

  EXPECT_TRUE(true);
}

TEST_F(RobotSimulatorTest, RunSimulatorWithEmptyCommandInput) {
  std::vector<std::string> lines;

  auto reader = std::make_unique<MockInputReader>(lines);
  auto parser = std::make_unique<CommandFactory>();
  auto ground = std::make_unique<SimulatorGround>(5, 5);

  RobotSimulator sim(std::move(reader), std::move(parser), std::move(ground));

  clearOutput();
  sim.run();

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("No input lines to process"), std::string::npos);
}

TEST_F(RobotSimulatorTest, RunSimulatorWithSingleCommandInput) {
  std::vector<std::string> lines{"PLACE 0,0,NORTH"};

  auto reader = std::make_unique<MockInputReader>(lines);
  auto parser = std::make_unique<CommandFactory>();
  auto ground = std::make_unique<SimulatorGround>(5, 5);

  RobotSimulator sim(std::move(reader), std::move(parser), std::move(ground));

  clearOutput();
  sim.run();

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("robot placed at 0,0 facing NORTH"), std::string::npos);
  EXPECT_NE(output.find("Simulation completed with 0 Errors."), std::string::npos);
}

TEST_F(RobotSimulatorTest, RunSimulatorWithMultipleCommandsInput) {
  std::vector<std::string> lines{"PLACE 0,0,NORTH", "MOVE", "REPORT"};

  auto reader = std::make_unique<MockInputReader>(lines);
  auto parser = std::make_unique<CommandFactory>();
  auto ground = std::make_unique<SimulatorGround>(5, 5);

  RobotSimulator sim(std::move(reader), std::move(parser), std::move(ground));

  clearOutput();
  sim.run();

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("Output: 0,1,NORTH"), std::string::npos);
  EXPECT_NE(output.find("Simulation completed with 0 Errors."), std::string::npos);
}

TEST_F(RobotSimulatorTest, RunSimulatorWithInvalidCommandsInput) {
  std::vector<std::string> lines{"INVALID_COMMAND"};

  auto reader = std::make_unique<MockInputReader>(lines);
  auto parser = std::make_unique<CommandFactory>();
  auto ground = std::make_unique<SimulatorGround>(5, 5);

  RobotSimulator sim(std::move(reader), std::move(parser), std::move(ground));

  clearOutput();
  sim.run();

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("Parse error on line"), std::string::npos);
  EXPECT_NE(output.find("Simulation completed with 1 Errors"), std::string::npos);
}

TEST_F(RobotSimulatorTest, RunSimulatorWithEdgeViolation) {
  std::vector<std::string> lines{"PLACE 0,0,NORTH", "MOVE", "MOVE", "MOVE"};

  auto reader = std::make_unique<MockInputReader>(lines);
  auto parser = std::make_unique<CommandFactory>();
  auto ground = std::make_unique<SimulatorGround>(2, 2);

  RobotSimulator sim(std::move(reader), std::move(parser), std::move(ground));

  clearOutput();
  sim.run();

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("position out of bounds"), std::string::npos);
  EXPECT_NE(output.find("Simulation completed with 2 Errors."), std::string::npos);
}

TEST_F(RobotSimulatorTest, RunSimulatorWithMultiplePlaceCommands) {
  std::vector<std::string> lines{"PLACE 0,0,NORTH", "REPORT", "PLACE 4,4,SOUTH", "REPORT", "PLACE 2,2,EAST", "REPORT"};

  auto reader = std::make_unique<MockInputReader>(lines);
  auto parser = std::make_unique<CommandFactory>();
  auto ground = std::make_unique<SimulatorGround>(5, 5);

  RobotSimulator sim(std::move(reader), std::move(parser), std::move(ground));

  clearOutput();
  sim.run();

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("Output: 0,0,NORTH"), std::string::npos);
  EXPECT_NE(output.find("Output: 4,4,SOUTH"), std::string::npos);
  EXPECT_NE(output.find("Output: 2,2,EAST"), std::string::npos);
  EXPECT_NE(output.find("Simulation completed with 0 Errors."), std::string::npos);
}

TEST_F(RobotSimulatorTest, RunSimulatorMultipleInvalidCommandsInput) {
  std::vector<std::string> lines{"INVALID1", "INVALID2", "INVALID3"};

  auto reader = std::make_unique<MockInputReader>(lines);
  auto parser = std::make_unique<CommandFactory>();
  auto ground = std::make_unique<SimulatorGround>(5, 5);

  RobotSimulator sim(std::move(reader), std::move(parser), std::move(ground));

  clearOutput();
  sim.run();

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("Simulation completed with 3 Errors"), std::string::npos);
}
