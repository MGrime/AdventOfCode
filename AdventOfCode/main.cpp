#include <iostream>

#include "utility/constants.hpp"
#include "utility/funcs.hpp"

#include "tasks/execution_map.hpp"

int main()
{
	std::cout << "Welcome to Advent Of Code 2021!. Enter a day to run test for: ";
	auto day = aoc::readNum(std::cin);

	// 0 means failure, and limit to below completed days and cannot be negative
	while (day <= 0 || day > aoc::MAX_DAYS)
	{
		std::cout << "\nEnter a value between 1 and " << aoc::MAX_DAYS << ": ";
		day = aoc::readNum(std::cin);
	}

	// Execute
	aoc::EXECUTION_MAP.at(day)();

}