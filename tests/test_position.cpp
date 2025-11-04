#include <gtest/gtest.h>

#include "Position.hpp"

using namespace simulator;

class PositionTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(PositionTest, DefaultConstructorZero) {
  Position p;

  EXPECT_EQ(p.x, 0);
  EXPECT_EQ(p.y, 0);
}

TEST_F(PositionTest, ParameterizedConstructor) {
  Position p{1, 2};

  EXPECT_EQ(p.x, 1);
  EXPECT_EQ(p.y, 2);
}

TEST_F(PositionTest, ConstructorNegativeCoordinates) {
  Position p{-1, -5};

  EXPECT_EQ(p.x, -1);
  EXPECT_EQ(p.y, -5);
}

TEST_F(PositionTest, SameEqualityOperator) {
  Position p1{1, 2};
  Position p2{1, 2};

  EXPECT_TRUE(p1 == p2);
}

TEST_F(PositionTest, SelfEqualityOperator) {
  Position p1{1, 2};

  EXPECT_TRUE(p1 == p1);
}

TEST_F(PositionTest, NotEqualityOperator) {
  Position p1{1, 2};
  Position p2{2, 1};

  EXPECT_TRUE(p1 != p2);
}

TEST_F(PositionTest, StreamOutput) {
  Position p1{1, 2};

  std::ostringstream oss;
  oss << p1;
  EXPECT_EQ(oss.str(), "1,2");
}
