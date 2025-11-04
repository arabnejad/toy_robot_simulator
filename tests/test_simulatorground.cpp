#include <gtest/gtest.h>

#include "SimulatorException.hpp"
#include "SimulatorGround.hpp"

using namespace simulator;

class SimulatorGroundTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}

  SimulatorGround ground{5, 5};
};

TEST_F(SimulatorGroundTest, GetRowsAndCols) {
  EXPECT_EQ(ground.getRows(), 5);
  EXPECT_EQ(ground.getCols(), 5);
}

TEST_F(SimulatorGroundTest, InvalidNegativeRowsForConstructor) {
  EXPECT_THROW(SimulatorGround(-1, 5), InvalidInputException);
}

TEST_F(SimulatorGroundTest, InvalidNegativeColsForConstructor) {
  EXPECT_THROW(SimulatorGround(5, -1), InvalidInputException);
}

TEST_F(SimulatorGroundTest, InvalidZeroRowsForConstructor) {
  EXPECT_THROW(SimulatorGround(0, 5), InvalidInputException);
}

TEST_F(SimulatorGroundTest, InvalidZeroColsForConstructor) {
  EXPECT_THROW(SimulatorGround(5, 0), InvalidInputException);
}

TEST_F(SimulatorGroundTest, InvalidZeroColsAndRowsForConstructor) {
  EXPECT_THROW(SimulatorGround(0, 0), InvalidInputException);
}

TEST_F(SimulatorGroundTest, IsValidPosition) {
  EXPECT_TRUE(ground.isValidPosition({0, 0}));
}

TEST_F(SimulatorGroundTest, IsValidPositionWithCorners) {
  EXPECT_TRUE(ground.isValidPosition({0, 0}));
  EXPECT_TRUE(ground.isValidPosition({4, 0}));
  EXPECT_TRUE(ground.isValidPosition({0, 4}));
  EXPECT_TRUE(ground.isValidPosition({4, 4}));
}

TEST_F(SimulatorGroundTest, InvalidPositionForNegativeXpos) {
  EXPECT_FALSE(ground.isValidPosition({-1, 2}));
}

TEST_F(SimulatorGroundTest, InvalidPositionForNegativeYpos) {
  EXPECT_FALSE(ground.isValidPosition({2, -1}));
}

TEST_F(SimulatorGroundTest, InvalidPositionForNegativeXY) {
  EXPECT_FALSE(ground.isValidPosition({-1, -1}));
}

TEST_F(SimulatorGroundTest, InvalidPositionForOutOfRangeXpos) {
  EXPECT_FALSE(ground.isValidPosition({5, 2}));
}

TEST_F(SimulatorGroundTest, InvalidPositionForOutOfRangeYpos) {
  EXPECT_FALSE(ground.isValidPosition({2, 5}));
}

TEST_F(SimulatorGroundTest, InvalidPositionForOutOfRangeXYpos) {
  EXPECT_FALSE(ground.isValidPosition({5, 5}));
}
