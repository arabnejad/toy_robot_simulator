#include <gtest/gtest.h>

#include "Command.hpp"
#include "Robot.hpp"
#include "SimulatorException.hpp"
#include "SimulatorGround.hpp"
#include "utils.hpp"

using namespace simulator;

class CommandTest : public ::testing::Test {
protected:
  Robot           robot  = Robot();
  SimulatorGround ground = SimulatorGround(5, 5);

  // https://github.com/arabnejad/cppColorLog/blob/master/tests/test_logger.cpp
  std::stringstream capturedCout;
  std::streambuf   *oldCout = nullptr;

  void SetUp() override {
    // Redirect std::cout to capturedCout
    oldCout = std::cout.rdbuf(capturedCout.rdbuf());
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

TEST_F(CommandTest, PlaceCommandWithValidPosition) {
  Position     pos{2, 3};
  PlaceCommand cmd(pos, Direction::NORTH);

  cmd.execute(robot, ground);

  EXPECT_TRUE(robot.hasPlaced());
  EXPECT_EQ(robot.getPosition(), pos);
  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
}

TEST_F(CommandTest, ThrowByPlaceCommandWithNegativeXpos) {
  Position     pos{-1, 2};
  PlaceCommand cmd(pos, Direction::NORTH);

  EXPECT_THROW(cmd.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, ThrowByPlaceCommandWithNegativeYpos) {
  Position     pos{2, -1};
  PlaceCommand cmd(pos, Direction::NORTH);

  EXPECT_THROW(cmd.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, ThrowByPlaceCommandWithOutOfEdgeXpos) {
  Position     pos{5, 2};
  PlaceCommand cmd(pos, Direction::NORTH);

  EXPECT_THROW(cmd.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, ThrowByPlaceCommandWithOutOfEdgeYpos) {
  Position     pos{2, 5};
  PlaceCommand cmd(pos, Direction::NORTH);

  EXPECT_THROW(cmd.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, OverridePreviousPlaceCommand) {
  Position     pos1{1, 1};
  PlaceCommand cmd1(pos1, Direction::NORTH);

  Position     pos2{3, 3};
  PlaceCommand cmd2(pos2, Direction::SOUTH);

  cmd1.execute(robot, ground);
  cmd2.execute(robot, ground);

  EXPECT_EQ(robot.getPosition(), pos2);
  EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
}

TEST_F(CommandTest, ThrowByMoveCommandForNotPlacedRobot) {
  MoveCommand cmd;

  EXPECT_THROW(cmd.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, MoveCommandToNorth) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::NORTH);
  MoveCommand  move;

  place.execute(robot, ground);
  move.execute(robot, ground);

  EXPECT_EQ(robot.getPosition().x, pos.x);
  EXPECT_EQ(robot.getPosition().y, pos.y + 1);
  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
}

TEST_F(CommandTest, MoveCommandToSouth) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::SOUTH);
  MoveCommand  move;

  place.execute(robot, ground);
  move.execute(robot, ground);

  EXPECT_EQ(robot.getPosition().x, pos.x);
  EXPECT_EQ(robot.getPosition().y, pos.y - 1);
  EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
}

TEST_F(CommandTest, MoveCommandToEast) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::EAST);
  MoveCommand  move;

  place.execute(robot, ground);
  move.execute(robot, ground);

  EXPECT_EQ(robot.getPosition().x, pos.x + 1);
  EXPECT_EQ(robot.getPosition().y, pos.y);
  EXPECT_EQ(robot.getDirection(), Direction::EAST);
}

TEST_F(CommandTest, MoveCommandToWest) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::WEST);
  MoveCommand  move;

  place.execute(robot, ground);
  move.execute(robot, ground);

  EXPECT_EQ(robot.getPosition().x, pos.x - 1);
  EXPECT_EQ(robot.getPosition().y, pos.y);
  EXPECT_EQ(robot.getDirection(), Direction::WEST);
}

TEST_F(CommandTest, ThrowByMoveCommandOutOfEdgeAtNorthWestFacedNorth) {
  Position     pos{0, 4};
  PlaceCommand place(pos, Direction::NORTH);
  MoveCommand  move;

  place.execute(robot, ground);

  EXPECT_THROW(move.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, ThrowByMoveCommandOutOfEdgeAtNorthWestFacedWest) {
  Position     pos{0, 4};
  PlaceCommand place(pos, Direction::WEST);
  MoveCommand  move;

  place.execute(robot, ground);

  EXPECT_THROW(move.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, ThrowByMoveCommandOutOfEdgeAtSouthEastFacedSouth) {
  Position     pos{4, 0};
  PlaceCommand place(pos, Direction::SOUTH);
  MoveCommand  move;

  place.execute(robot, ground);

  EXPECT_THROW(move.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, ThrowByMoveCommandOutOfEdgeAtSouthEastFacedEast) {
  Position     pos{4, 0};
  PlaceCommand place(pos, Direction::EAST);
  MoveCommand  move;

  place.execute(robot, ground);

  EXPECT_THROW(move.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, ThrowByLeftCommandForNotPlacedRobot) {
  LeftCommand cmd;

  EXPECT_THROW(cmd.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, LeftCommandFromNorthToWest) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::NORTH);
  LeftCommand  left;

  place.execute(robot, ground);
  left.execute(robot, ground);

  EXPECT_EQ(robot.getDirection(), Direction::WEST);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(CommandTest, LeftCommandFromWestToSouth) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::WEST);
  LeftCommand  left;

  place.execute(robot, ground);
  left.execute(robot, ground);

  EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(CommandTest, LeftCommandFromSouthToEast) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::SOUTH);
  LeftCommand  left;

  place.execute(robot, ground);
  left.execute(robot, ground);

  EXPECT_EQ(robot.getDirection(), Direction::EAST);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(CommandTest, LeftCommandFromEastToNorth) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::EAST);
  LeftCommand  left;

  place.execute(robot, ground);
  left.execute(robot, ground);

  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(CommandTest, ThrowByRightCommandForNotPlacedRobot) {
  RightCommand cmd;

  EXPECT_THROW(cmd.execute(robot, ground), InvalidInputException);
}

TEST_F(CommandTest, RightCommandFromNorthToEast) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::NORTH);
  RightCommand right;

  place.execute(robot, ground);
  right.execute(robot, ground);

  EXPECT_EQ(robot.getDirection(), Direction::EAST);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(CommandTest, RightCommandFromEastToSouth) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::EAST);
  RightCommand right;

  place.execute(robot, ground);
  right.execute(robot, ground);

  EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(CommandTest, RightCommandFromSouthToWest) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::SOUTH);
  RightCommand right;

  place.execute(robot, ground);
  right.execute(robot, ground);

  EXPECT_EQ(robot.getDirection(), Direction::WEST);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(CommandTest, RightCommandFromWestToNorth) {
  Position     pos{2, 2};
  PlaceCommand place(pos, Direction::WEST);
  RightCommand right;

  place.execute(robot, ground);
  right.execute(robot, ground);

  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(CommandTest, ReportCommandForNotPlacedRobot) {
  ReportCommand cmd;
  cmd.execute(robot, ground);

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("not placed"), std::string::npos);
}

TEST_F(CommandTest, ReportCommandPlacedRobot) {
  Position     pos{2, 3};
  PlaceCommand place(pos, Direction::NORTH);
  place.execute(robot, ground);

  clearOutput();

  ReportCommand report;
  report.execute(robot, ground);

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("2"), std::string::npos);
  EXPECT_NE(output.find("3"), std::string::npos);
  EXPECT_NE(output.find("NORTH"), std::string::npos);
  EXPECT_EQ(output, "Output: 2,3,NORTH\n");
}
