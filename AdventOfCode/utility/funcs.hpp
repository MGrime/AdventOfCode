#pragma once
#include <istream>
#include <string>
#include <vector>

namespace aoc
{
	int parseDigit(char digit);
	int readNum(std::istream& in);
	std::vector<std::string> readFile(const char* path);
}