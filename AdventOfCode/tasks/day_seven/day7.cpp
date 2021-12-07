#include "day7.hpp"
#include "../../utility/funcs.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

namespace aoc::d7
{
	const char* inputPath = "day_seven.txt";

	std::vector<int> horizontalPositions;

	void execute()
	{
		// Read input
		auto input = readFile(inputPath);

		std::string numBuff = "";
		for (const auto& line : input)
		{
			for (const auto& digit : line)
			{
				if (digit == ',' && numBuff != "")
				{
					horizontalPositions.push_back(std::stoi(numBuff));
					numBuff = "";
				}
				else
				{
					numBuff += digit;
				}
			}
		}

		// Last one
		horizontalPositions.push_back(std::stoi(numBuff));
		numBuff = "";
		
		std::vector<int> diffArray{};

		// Get max value in list
		const auto maxPosition = *std::max_element(horizontalPositions.begin(),horizontalPositions.end());

		// Resize array
		for (int i = 0; i < maxPosition; ++i)
		{
			diffArray.push_back(0);
		}

		// Loop to that value
		for (int i = 0; i < maxPosition; ++i)
		{
			// Loop each position
			for (int j = 0; j < horizontalPositions.size(); ++j)
			{
				// Sum diff into array
				const auto diff = std::abs(horizontalPositions[j] - i);
				diffArray[i] += diff * (diff + 1) / 2;
			}
		}

		// Get the smallest value
		const auto smallestValue = std::min_element(diffArray.begin(), diffArray.end());

		std::cout << "Part 2: " << *smallestValue;

	}
}