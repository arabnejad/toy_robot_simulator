#include <gtest/gtest.h>
#include <sstream>

#include "ArgParser.hpp"
#include "SimulatorException.hpp"

using namespace simulator;

class ArgParserTest : public ::testing::Test {
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(ArgParserTest, HelpFlagLong) {
  const char *argv[] = {"simulator", "--help"};
  ArgParser   parser(2, const_cast<char **>(argv));

  parser.parse();

  EXPECT_TRUE(parser.showHelpMessage());
}

TEST_F(ArgParserTest, HelpFlagShort) {
  const char *argv[] = {"simulator", "-h"};
  ArgParser   parser(2, const_cast<char **>(argv));

  parser.parse();

  EXPECT_TRUE(parser.showHelpMessage());
}

TEST_F(ArgParserTest, ValidFileArg) {
  const char *argv[] = {"simulator", "--file", "input.txt"};
  ArgParser   parser(3, const_cast<char **>(argv));

  parser.parse();

  EXPECT_TRUE(parser.hasInputFile());
  EXPECT_EQ(parser.getInputFile(), "input.txt");
}

TEST_F(ArgParserTest, MissingFileArgValue) {
  const char *argv[] = {"simulator", "--file"};
  ArgParser   parser(2, const_cast<char **>(argv));

  EXPECT_THROW(parser.parse(), InvalidInputException);
}

TEST_F(ArgParserTest, ValidNoneLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel=NONE"};
  ArgParser   parser(2, const_cast<char **>(argv));

  parser.parse();

  EXPECT_EQ(parser.getLogLevel(), LogLevel::NONE);
}

TEST_F(ArgParserTest, ValidDebugLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel=DEBUG"};
  ArgParser   parser(2, const_cast<char **>(argv));

  parser.parse();

  EXPECT_EQ(parser.getLogLevel(), LogLevel::DEBUG);
}

TEST_F(ArgParserTest, ValidInfoLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel=INFO"};
  ArgParser   parser(2, const_cast<char **>(argv));

  parser.parse();

  EXPECT_EQ(parser.getLogLevel(), LogLevel::INFO);
}

TEST_F(ArgParserTest, ValidErrorLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel=ERROR"};
  ArgParser   parser(2, const_cast<char **>(argv));

  parser.parse();

  EXPECT_EQ(parser.getLogLevel(), LogLevel::ERROR);
}

TEST_F(ArgParserTest, ValidTraceLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel=TRACE"};
  ArgParser   parser(2, const_cast<char **>(argv));

  parser.parse();

  EXPECT_EQ(parser.getLogLevel(), LogLevel::TRACE);
}

TEST_F(ArgParserTest, ValidWarningLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel=WARNING"};
  ArgParser   parser(2, const_cast<char **>(argv));

  parser.parse();

  EXPECT_EQ(parser.getLogLevel(), LogLevel::WARNING);
}

TEST_F(ArgParserTest, MissingLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel"};
  ArgParser   parser(2, const_cast<char **>(argv));

  EXPECT_THROW(parser.parse(), InvalidInputException);
}

TEST_F(ArgParserTest, EmptyLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel="};
  ArgParser   parser(2, const_cast<char **>(argv));

  EXPECT_THROW(parser.parse(), InvalidInputException);
}

TEST_F(ArgParserTest, InvalidLogLevelArg) {
  const char *argv[] = {"simulator", "--loglevel=INVALID"};
  ArgParser   parser(2, const_cast<char **>(argv));

  EXPECT_THROW(parser.parse(), InvalidInputException);
}

TEST_F(ArgParserTest, ValidAllArgs) {
  const char *argv[] = {"simulator", "--file", "input.txt", "--loglevel=ERROR"};
  ArgParser   parser(4, const_cast<char **>(argv));

  parser.parse();

  EXPECT_TRUE(parser.hasInputFile());
  EXPECT_EQ(parser.getInputFile(), "input.txt");
  EXPECT_EQ(parser.getLogLevel(), LogLevel::ERROR);
}

TEST_F(ArgParserTest, UnknownArg) {
  const char *argv[] = {"simulator", "--unknown"};
  ArgParser   parser(2, const_cast<char **>(argv));

  EXPECT_THROW(parser.parse(), InvalidInputException);
}

TEST_F(ArgParserTest, PrintHelp) {
  const char          *argv[] = {"simulator", "--help"};
  simulator::ArgParser p(2, const_cast<char **>(argv));
  std::ostringstream   ostream;

  p.parse();
  p.printHelp(ostream);

  EXPECT_TRUE(p.showHelpMessage());
  auto out = ostream.str();
  EXPECT_NE(out.find("Usage:"), std::string::npos);
}