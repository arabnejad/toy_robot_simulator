#include <chrono>
#include <gtest/gtest.h>
#include <sstream>
#include <thread>

#include "Logger.hpp"

using namespace simulator;

class LoggerTest : public ::testing::Test {
protected:
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

TEST_F(LoggerTest, GetInstanceReturnsReference) {
  Logger &logger1 = Logger::getInstance();
  Logger &logger2 = Logger::getInstance();

  EXPECT_EQ(&logger1, &logger2);
}

TEST_F(LoggerTest, SingletonInstance) {
  Logger &logger = Logger::getInstance();

  EXPECT_NE(&logger, nullptr);
}

TEST_F(LoggerTest, SetLogLevelNone) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::NONE);

  EXPECT_EQ(logger.getLogLevel(), LogLevel::NONE);
}

TEST_F(LoggerTest, SetLogLevelError) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::ERROR);

  EXPECT_EQ(logger.getLogLevel(), LogLevel::ERROR);
}

TEST_F(LoggerTest, SetLogLevelWarning) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::WARNING);

  EXPECT_EQ(logger.getLogLevel(), LogLevel::WARNING);
}

TEST_F(LoggerTest, SetLogLevelInfo) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::INFO);

  EXPECT_EQ(logger.getLogLevel(), LogLevel::INFO);
}

TEST_F(LoggerTest, SetLogLevelDebug) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::DEBUG);

  EXPECT_EQ(logger.getLogLevel(), LogLevel::DEBUG);
}

TEST_F(LoggerTest, SetLogLevelTrace) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::TRACE);

  EXPECT_EQ(logger.getLogLevel(), LogLevel::TRACE);
}

TEST_F(LoggerTest, DefaultLogLevel) {
  Logger &logger = Logger::getInstance();

  EXPECT_EQ(logger.getLogLevel(), LogLevel::INFO);
}

TEST_F(LoggerTest, getLogLevelAsStringNone) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::NONE);

  EXPECT_EQ(logger.getLogLevelAsString(), "NONE");
}

TEST_F(LoggerTest, getLogLevelAsStringError) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::ERROR);

  EXPECT_EQ(logger.getLogLevelAsString(), "ERROR");
}

TEST_F(LoggerTest, getLogLevelAsStringWarning) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::WARNING);

  EXPECT_EQ(logger.getLogLevelAsString(), "WARNING");
}

TEST_F(LoggerTest, getLogLevelAsStringInfo) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::INFO);

  EXPECT_EQ(logger.getLogLevelAsString(), "INFO");
}

TEST_F(LoggerTest, getLogLevelAsStringDebug) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::DEBUG);

  EXPECT_EQ(logger.getLogLevelAsString(), "DEBUG");
}

TEST_F(LoggerTest, getLogLevelAsStringTrace) {
  Logger &logger = Logger::getInstance();

  logger.setLogLevel(LogLevel::TRACE);

  EXPECT_EQ(logger.getLogLevelAsString(), "TRACE");
}

TEST_F(LoggerTest, LogLevelNoneDisablesAllLogging) {
  Logger &logger = Logger::getInstance();
  logger.setLogLevel(LogLevel::NONE);

  clearOutput();
  logger.error("Error");
  logger.warning("Warning");
  logger.info("Info");
  logger.debug("Debug");
  logger.trace("Trace");

  std::string output = getCapturedOutput();
  EXPECT_TRUE(output.empty());
}

TEST_F(LoggerTest, LogLevelErrorOnlyShowsErrors) {
  Logger &logger = Logger::getInstance();
  logger.setLogLevel(LogLevel::ERROR);

  clearOutput();
  logger.error("Error");
  logger.warning("Warning");

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("Error"), std::string::npos);
  EXPECT_EQ(output.find("Warning"), std::string::npos);
}

TEST_F(LoggerTest, LogLevelTraceShowsAll) {
  Logger &logger = Logger::getInstance();
  logger.setLogLevel(LogLevel::TRACE);

  clearOutput();
  logger.error("Error");
  logger.warning("Warning");
  logger.info("Info");
  logger.debug("Debug");
  logger.trace("Trace");

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("Error"), std::string::npos);
  EXPECT_NE(output.find("Warning"), std::string::npos);
  EXPECT_NE(output.find("Info"), std::string::npos);
  EXPECT_NE(output.find("Debug"), std::string::npos);
  EXPECT_NE(output.find("Trace"), std::string::npos);
}

TEST_F(LoggerTest, LogFormatContainsTimestamp) {
  Logger &logger = Logger::getInstance();
  logger.setLogLevel(LogLevel::INFO);

  clearOutput();
  logger.info("Test");

  std::string output = getCapturedOutput();
  // Check for timestamp format (YYYY-MM-DD HH:MM:SS)
  EXPECT_NE(output.find("[20"), std::string::npos); // Year starts with 20xx
}

TEST_F(LoggerTest, LogFormatContainsLevel) {
  Logger &logger = Logger::getInstance();
  logger.setLogLevel(LogLevel::DEBUG);

  clearOutput();
  logger.debug("Test");

  std::string output = getCapturedOutput();
  EXPECT_NE(output.find("[DEBUG  ]"), std::string::npos);
}

TEST_F(LoggerTest, EmptyMessage) {
  Logger &logger = Logger::getInstance();
  logger.setLogLevel(LogLevel::INFO);

  clearOutput();
  logger.info("");

  std::string output = getCapturedOutput();
  // Should still output timestamp and level
  EXPECT_NE(output.find("INFO"), std::string::npos);
  EXPECT_NE(output.find("[20"), std::string::npos); // Year starts with 20xx
}

TEST_F(LoggerTest, LogLevelStreamOperatorUnknown) {
  std::ostringstream oss;

  // Cast an invalid value to LogLevel to trigger UNKNOWN case
  LogLevel unknown = static_cast<LogLevel>(999);
  oss << unknown;

  EXPECT_EQ(oss.str(), "UNKNOWN");
}