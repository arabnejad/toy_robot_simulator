#include <exception>
#include <gtest/gtest.h>
#include <string>

#include "SimulatorException.hpp"

using namespace simulator;

class SimulatorExceptionTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(SimulatorExceptionTest, BaseExceptionMessage) {
  std::string msg = "Custom error message";

  SimulatorException ex(msg);

  EXPECT_EQ(std::string(ex.what()), msg);
}

TEST_F(SimulatorExceptionTest, BaseExceptionEmptyMessage) {
  SimulatorException ex("");

  EXPECT_STREQ(ex.what(), "");
}

TEST_F(SimulatorExceptionTest, FileExceptionFileName) {
  FileException ex("config.ini");

  EXPECT_STREQ(ex.what(), "Cannot open or read file: config.ini");
}

TEST_F(SimulatorExceptionTest, FileExceptionEmptyFileName) {
  FileException ex("");

  EXPECT_STREQ(ex.what(), "Cannot open or read file: ");
}

TEST_F(SimulatorExceptionTest, ParseExceptionSingleArgConstructor) {
  ParseException ex("Invalid syntax");
  std::string    msg(ex.what());

  EXPECT_NE(msg.find("Parse error:"), std::string::npos);
  EXPECT_NE(msg.find("Invalid syntax"), std::string::npos);
}

TEST_F(SimulatorExceptionTest, ParseExceptionTwoArgConstructor) {
  ParseException ex("Unexpected token", 42);
  std::string    msg(ex.what());

  EXPECT_NE(msg.find("Parse error at line 42:"), std::string::npos);
  EXPECT_NE(msg.find("Unexpected token"), std::string::npos);
}

TEST_F(SimulatorExceptionTest, InvalidInputExceptionMessage) {
  InvalidInputException ex("Coordinates out of range");

  EXPECT_STREQ(ex.what(), "Invalid input: Coordinates out of range");
}

TEST_F(SimulatorExceptionTest, FileExceptionCanBeCaught) {
  try {
    throw FileException("missing.txt");
  } catch (const FileException &e) {
    std::string msg(e.what());
    EXPECT_NE(msg.find("missing.txt"), std::string::npos);
  }
}

TEST_F(SimulatorExceptionTest, BaseExceptionCanBeCaught) {
  try {
    throw SimulatorException("Test exception");
  } catch (const SimulatorException &e) {
    EXPECT_STREQ(e.what(), "Test exception");
  } catch (...) {
    FAIL() << "Exception not caught as SimulatorException";
  }
}

TEST_F(SimulatorExceptionTest, ParseExceptionCanBeCaught) {
  try {
    throw ParseException("Syntax error", 5);
  } catch (const ParseException &e) {
    std::string msg(e.what());
    EXPECT_NE(msg.find("line 5"), std::string::npos);
  } catch (...) {
    FAIL() << "Not caught as ParseException";
  }
}

TEST_F(SimulatorExceptionTest, InvalidInputExceptionCanBeCaught) {
  try {
    throw InvalidInputException("Negative value");
  } catch (const InvalidInputException &e) {
    EXPECT_STREQ(e.what(), "Invalid input: Negative value");
  } catch (...) {
    FAIL() << "Not caught as InvalidInputException";
  }
}
