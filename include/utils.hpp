#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define UNUSED(x) (void)(x)

std::vector<std::string> split(const std::string &s, const char delimiter);
std::string              trim(const std::string &s);
std::string              toUpperCase(const std::string &str);