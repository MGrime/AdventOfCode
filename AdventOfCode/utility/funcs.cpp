#include "funcs.hpp"

#include <iostream>
#include <fstream>

namespace aoc
{
	int parseDigit(char digit)
	{
		return digit - '0';
	}

	int readNum(std::istream& in)
	{
		std::string buffer;
		std::getline(in, buffer);

		if (buffer.empty())
		{
			return -1;
		}

		return parseDigit(buffer.at(0));

	}
	std::vector<std::string> readFile(const char* path)
	{
		// Open input text
		std::ifstream file;

		file.open(path);
		if (file.fail())
		{
			std::cout << "Failed to open input file!";
			return std::vector<std::string>();
		}

		std::string str;
		std::vector<std::string> input;

		// Read lines
		while (std::getline(file, str))
		{
			input.push_back(str);
		}
		file.close();

		return input;
	}
}