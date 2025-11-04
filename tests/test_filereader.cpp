#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include <sys/stat.h>

#include "FileReader.hpp"
#include "SimulatorException.hpp"

using namespace simulator;

class FileReaderTest : public ::testing::Test {
protected:
  std::string test_dir = "/tmp/fileReaderTest_" + std::to_string(std::rand());

  void SetUp() override {
    std::string cmd = "mkdir -p " + test_dir;
    system(cmd.c_str());
  }

  void TearDown() override {
    // Clean up test directory using system call
    std::string cmd = "rm -rf " + test_dir;
    system(cmd.c_str());
  }

  std::string createTestFile(const std::string &filename, const std::string &content) {
    std::string   filepath = test_dir + "/" + filename;
    std::ofstream file(filepath);
    if (file.is_open()) {
      file << content;
      file.close();
    }
    return filepath;
  }

  std::string createEmptyFile(const std::string &filename) {
    std::string   filepath = test_dir + "/" + filename;
    std::ofstream file(filepath);
    file.close();
    return filepath;
  }
};

TEST_F(FileReaderTest, ReadSingleLine) {
  std::string filepath = createTestFile("input.txt", "PLACE 1,2,NORTH");
  FileReader  reader(filepath);

  auto lines = reader.readInput();

  EXPECT_EQ(lines.size(), 1);
  EXPECT_EQ(lines[0], "PLACE 1,2,NORTH");
}

TEST_F(FileReaderTest, ReadFileWithMultipleLines) {
  std::string content  = "PLACE 0,0,NORTH\nMOVE\nLEFT\nREPORT";
  std::string filepath = createTestFile("input.txt", content);
  FileReader  reader(filepath);

  auto lines = reader.readInput();

  EXPECT_EQ(lines.size(), 4);
  EXPECT_EQ(lines[0], "PLACE 0,0,NORTH");
  EXPECT_EQ(lines[1], "MOVE");
  EXPECT_EQ(lines[2], "LEFT");
  EXPECT_EQ(lines[3], "REPORT");
}

TEST_F(FileReaderTest, ReadEmptyFile) {
  std::string filepath = createEmptyFile("empty.txt");
  FileReader  reader(filepath);

  auto lines = reader.readInput();

  EXPECT_EQ(lines.size(), 0);
  EXPECT_TRUE(lines.empty());
}

TEST_F(FileReaderTest, NonExistentFile) {
  FileReader reader("/somewhere/unknown/path/file.txt");

  EXPECT_THROW(reader.readInput(), FileException);
}
