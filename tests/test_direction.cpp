#include <gtest/gtest.h>

#include "Direction.hpp"

using namespace simulator;

class DirectionTest : public ::testing::Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(DirectionTest, StreamOperatorNorth) {
  std::ostringstream oss;

  oss << Direction::NORTH;

  EXPECT_EQ(oss.str(), "NORTH");
}

TEST_F(DirectionTest, StreamOperatorEAST) {
  std::ostringstream oss;

  oss << Direction::EAST;

  EXPECT_EQ(oss.str(), "EAST");
}

TEST_F(DirectionTest, StreamOperatorSOUTH) {
  std::ostringstream oss;

  oss << Direction::SOUTH;

  EXPECT_EQ(oss.str(), "SOUTH");
}

TEST_F(DirectionTest, StreamOperatorWEST) {
  std::ostringstream oss;

  oss << Direction::WEST;

  EXPECT_EQ(oss.str(), "WEST");
}

TEST_F(DirectionTest, StreamOperatorUnknown) {
  std::ostringstream oss;

  // Cast an invalid value to Direction to trigger UNKNOWN case
  Direction unknown = static_cast<Direction>(999);
  oss << unknown;

  EXPECT_EQ(oss.str(), "UNKNOWN");
}