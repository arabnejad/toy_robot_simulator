#include <gtest/gtest.h>

#include "CommandFactory.hpp"
#include "SimulatorException.hpp"

using namespace simulator;

class CommandFactoryTest : public ::testing::Test {
protected:
  CommandFactory factory;
};

TEST_F(CommandFactoryTest, ParsePlaceCommandValid) {
  auto cmd = factory.parse("PLACE 1,2,NORTH");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParsePlaceCommandUpperAndLowerCase) {
  auto cmd = factory.parse("Place 1,2,North");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParsePlaceCommandAllDirections) {
  auto cmd1 = factory.parse("PLACE 0,0,NORTH");
  auto cmd2 = factory.parse("PLACE 0,0,EAST");
  auto cmd3 = factory.parse("PLACE 0,0,SOUTH");
  auto cmd4 = factory.parse("PLACE 0,0,WEST");

  EXPECT_NE(cmd1, nullptr);
  EXPECT_NE(cmd2, nullptr);
  EXPECT_NE(cmd3, nullptr);
  EXPECT_NE(cmd4, nullptr);
}

TEST_F(CommandFactoryTest, ParsePlaceCommandWithSpaces) {
  auto cmd = factory.parse("  PLACE  1 , 2 , NORTH  ");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ThrowByParsePlaceCommandNoParameters) {
  EXPECT_THROW(factory.parse("PLACE"), ParseException);
}

TEST_F(CommandFactoryTest, ThrowByParsePlaceCommandTooFewParameters) {
  EXPECT_THROW(factory.parse("PLACE 1,2"), ParseException);
}

TEST_F(CommandFactoryTest, ThrowByParsePlaceCommandTooManyParameters) {
  EXPECT_THROW(factory.parse("PLACE 1,2,NORTH,WOW"), ParseException);
}

TEST_F(CommandFactoryTest, ThrowByParsePlaceCommandInvalidX) {
  EXPECT_THROW(factory.parse("PLACE abc,2,NORTH"), ParseException);
}

TEST_F(CommandFactoryTest, ThrowByParsePlaceCommandInvalidY) {
  EXPECT_THROW(factory.parse("PLACE 1,xyz,NORTH"), ParseException);
}

TEST_F(CommandFactoryTest, ThrowByParsePlaceCommandInvalidDirection) {
  EXPECT_THROW(factory.parse("PLACE 1,2,INVALID"), ParseException);
}

TEST_F(CommandFactoryTest, ThrowByParsePlaceCommandEmptyDirection) {
  EXPECT_THROW(factory.parse("PLACE 1,2,"), ParseException);
}

TEST_F(CommandFactoryTest, ParseMoveCommand) {
  auto cmd = factory.parse("MOVE");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseMoveCommandLoweUpperCase) {
  auto cmd = factory.parse("Move");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseMoveCommandWithSpaces) {
  auto cmd = factory.parse("  MOVE  ");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseLeftCommand) {
  auto cmd = factory.parse("LEFT");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseLeftCommandLowerUpperCase) {
  auto cmd = factory.parse("Left");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseLeftCommandWithSpaces) {
  auto cmd = factory.parse("  LEFT  ");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseRightCommand) {
  auto cmd = factory.parse("RIGHT");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseRightCommandLowerUpperCase) {
  auto cmd = factory.parse("Right");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseRightCommandWithSpaces) {
  auto cmd = factory.parse("  RIGHT  ");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseReportCommand) {
  auto cmd = factory.parse("REPORT");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseReportCommandLowerUpperCase) {
  auto cmd = factory.parse("Report");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ParseReportCommandWithSpaces) {
  auto cmd = factory.parse("  REPORT  ");

  EXPECT_NE(cmd, nullptr);
}

TEST_F(CommandFactoryTest, ThrowByParseEmptyString) {
  EXPECT_THROW(factory.parse(""), ParseException);
}

TEST_F(CommandFactoryTest, ThrowByParseOnlySpaces) {
  EXPECT_THROW(factory.parse("   "), ParseException);
}
