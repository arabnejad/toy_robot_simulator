#include <gtest/gtest.h>

#include "Robot.hpp"
#include "SimulatorException.hpp"

using namespace simulator;

class RobotTest : public ::testing::Test {
protected:
  void  SetUp() override {}
  void  TearDown() override {}
  Robot robot;
};

TEST_F(RobotTest, InitiallyNotPlaced) {
  EXPECT_FALSE(robot.hasPlaced());
}

TEST_F(RobotTest, ValidPlaceRobot) {
  Position pos{2, 3};

  robot.place(pos, Direction::NORTH);

  EXPECT_TRUE(robot.hasPlaced());
  EXPECT_EQ(robot.getPosition(), pos);
  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
}

TEST_F(RobotTest, MultipleValidPlaceCommand) {
  Position pos1{2, 3};
  Position pos2{4, 1};

  robot.place(pos1, Direction::NORTH);
  robot.place(pos2, Direction::SOUTH);

  EXPECT_EQ(robot.getPosition(), pos2);
  EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
}

TEST_F(RobotTest, ThrowByGetPositionForNotPlacedRobot) {
  EXPECT_THROW({ robot.getPosition(); }, InvalidInputException);
}

TEST_F(RobotTest, ThrowByGetDirectionNotPlacedRobot) {
  EXPECT_THROW({ robot.getDirection(); }, InvalidInputException);
}

TEST_F(RobotTest, MoveNorth) {
  Position pos{2, 3};

  robot.place(pos, Direction::NORTH);
  robot.move();

  EXPECT_EQ(robot.getPosition().x, pos.x);
  EXPECT_EQ(robot.getPosition().y, pos.y + 1);
  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
}

TEST_F(RobotTest, MoveSouth) {
  Position pos{2, 3};

  robot.place(pos, Direction::SOUTH);
  robot.move();

  EXPECT_EQ(robot.getPosition().x, pos.x);
  EXPECT_EQ(robot.getPosition().y, pos.y - 1);
  EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
}

TEST_F(RobotTest, MoveEast) {
  Position pos{2, 3};

  robot.place(pos, Direction::EAST);
  robot.move();

  EXPECT_EQ(robot.getPosition().x, pos.x + 1);
  EXPECT_EQ(robot.getPosition().y, pos.y);
  EXPECT_EQ(robot.getDirection(), Direction::EAST);
}

TEST_F(RobotTest, MoveWest) {
  Position pos{2, 3};

  robot.place(pos, Direction::WEST);
  robot.move();

  EXPECT_EQ(robot.getPosition().x, pos.x - 1);
  EXPECT_EQ(robot.getPosition().y, pos.y);
  EXPECT_EQ(robot.getDirection(), Direction::WEST);
}

TEST_F(RobotTest, MoveMultipleTimes) {
  Position pos{1, 1};

  robot.place(pos, Direction::NORTH);
  robot.move();
  robot.move();
  robot.move();

  EXPECT_EQ(robot.getPosition().x, pos.x);
  EXPECT_EQ(robot.getPosition().y, pos.y + 3);
  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
}

TEST_F(RobotTest, ThrowByMoveNotPlacedRobot) {
  EXPECT_THROW({ robot.move(); }, InvalidInputException);
}

TEST_F(RobotTest, CalculateNextPositionForNorthDirection) {
  Position pos{2, 3};

  robot.place(pos, Direction::NORTH);
  Position next = robot.calculateNextPosition();

  EXPECT_EQ(next.x, pos.x);
  EXPECT_EQ(next.y, pos.y + 1);
}

TEST_F(RobotTest, CalculateNextPositionForSouthDirection) {
  Position pos{2, 3};

  robot.place(pos, Direction::SOUTH);
  Position next = robot.calculateNextPosition();

  EXPECT_EQ(next.x, pos.x);
  EXPECT_EQ(next.y, pos.y - 1);
}

TEST_F(RobotTest, CalculateNextPositionForEastDirection) {
  Position pos{2, 3};

  robot.place(pos, Direction::EAST);
  Position next = robot.calculateNextPosition();

  EXPECT_EQ(next.x, pos.x + 1);
  EXPECT_EQ(next.y, pos.y);
}

TEST_F(RobotTest, CalculateNextPositionForWestDirection) {
  Position pos{2, 3};

  robot.place(pos, Direction::WEST);
  Position next = robot.calculateNextPosition();

  EXPECT_EQ(next.x, pos.x - 1);
  EXPECT_EQ(next.y, pos.y);
}

TEST_F(RobotTest, ThrowByCalculateNextPositionForNotPlacedRobot) {
  EXPECT_THROW({ robot.calculateNextPosition(); }, InvalidInputException);
}

TEST_F(RobotTest, LeftRotateFromNorthToWest) {
  Position pos{2, 3};

  robot.place(pos, Direction::NORTH);
  robot.rotateLeft();

  EXPECT_EQ(robot.getDirection(), Direction::WEST);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(RobotTest, LeftRotateFromWestToSouth) {
  Position pos{2, 3};

  robot.place(pos, Direction::WEST);
  robot.rotateLeft();

  EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(RobotTest, LeftRotateFromSouthToEast) {
  Position pos{2, 3};

  robot.place(pos, Direction::SOUTH);
  robot.rotateLeft();

  EXPECT_EQ(robot.getDirection(), Direction::EAST);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(RobotTest, LeftRotateFromEastToNorth) {
  Position pos{2, 3};

  robot.place(pos, Direction::EAST);
  robot.rotateLeft();

  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(RobotTest, LeftRotateThrowsForNotPlacedRobot) {
  EXPECT_THROW({ robot.rotateLeft(); }, InvalidInputException);
}

TEST_F(RobotTest, RightRotateFromNorthToEast) {
  Position pos{2, 3};

  robot.place(pos, Direction::NORTH);
  robot.rotateRight();

  EXPECT_EQ(robot.getDirection(), Direction::EAST);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(RobotTest, RightRotateFromEastToSouth) {
  Position pos{2, 3};

  robot.place(pos, Direction::EAST);
  robot.rotateRight();

  EXPECT_EQ(robot.getDirection(), Direction::SOUTH);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(RobotTest, RightRotateFromSouthToWest) {
  Position pos{2, 3};

  robot.place(pos, Direction::SOUTH);
  robot.rotateRight();

  EXPECT_EQ(robot.getDirection(), Direction::WEST);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(RobotTest, RightRotateToWestToNorth) {
  Position pos{2, 3};

  robot.place(pos, Direction::WEST);
  robot.rotateRight();

  EXPECT_EQ(robot.getDirection(), Direction::NORTH);
  EXPECT_EQ(robot.getPosition(), pos);
}

TEST_F(RobotTest, RightRotateThrowsForNotPlacedRobot) {
  EXPECT_THROW({ robot.rotateRight(); }, InvalidInputException);
}
