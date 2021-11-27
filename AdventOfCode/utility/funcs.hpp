#pragma once
#include <istream>
#include <string>

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
}