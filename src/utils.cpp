#include "utils.hpp"

std::vector<std::string> split(const std::string &s, const char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream        ss(s);
  std::string              token;

  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

std::string trim(const std::string &s) {
  // Removes leading and trailing whitespace from a string
  auto start = s.find_first_not_of(" \t\r\n");
  auto end   = s.find_last_not_of(" \t\r\n");
  if (start == std::string::npos || end == std::string::npos)
    return "";
  return s.substr(start, end - start + 1);
}

std::string toUpperCase(const std::string &str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
  return result;
}
