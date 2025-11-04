#include <gtest/gtest.h>
#include <sstream>
#include <vector>

#include "ConsoleReader.hpp"
#include "SimulatorException.hpp"

using namespace simulator;

class ConsoleReaderTest : public ::testing::Test {
protected:
  ConsoleReader      reader;
  std::istringstream inputStream;
  std::streambuf    *oldCin;

  // https://www.reddit.com/r/cpp_questions/comments/1j2ppwt/how_do_you_test_a_function_that_interacts_with/
  void SetUp() override {
    // Save old std::cin buffer
    oldCin = std::cin.rdbuf();
  }

  void TearDown() override {
    // Restore std::cin
    std::cin.rdbuf(oldCin);
  }

  void sendStdCinInput(const std::string &msg) {
    inputStream.str(msg);
    std::cin.rdbuf(inputStream.rdbuf());
  }
};

TEST_F(ConsoleReaderTest, ReadSingleLine) {
  sendStdCinInput("PLACE 1,2,NORTH\n");

  auto lines = reader.readInput();

  EXPECT_EQ(lines.size(), 1);
  EXPECT_EQ(lines[0], "PLACE 1,2,NORTH");
}

TEST_F(ConsoleReaderTest, ReadMultipleLines) {
  sendStdCinInput("PLACE 0,0,NORTH\nMOVE\nLEFT\nREPORT\n");

  auto lines = reader.readInput();

  EXPECT_EQ(lines.size(), 4);
  EXPECT_EQ(lines[0], "PLACE 0,0,NORTH");
  EXPECT_EQ(lines[1], "MOVE");
  EXPECT_EQ(lines[2], "LEFT");
  EXPECT_EQ(lines[3], "REPORT");
}

TEST_F(ConsoleReaderTest, StopAtEmptyLine) {
  sendStdCinInput("PLACE 0,0,NORTH\nMOVE\n\nSHOULD_NO_BE_READ");

  auto lines = reader.readInput();

  EXPECT_EQ(lines.size(), 2);
  EXPECT_EQ(lines[0], "PLACE 0,0,NORTH");
  EXPECT_EQ(lines[1], "MOVE");
}
