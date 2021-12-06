#include "day6.hpp"
#include "../../utility/funcs.hpp"
#include <vector>
#include <iostream>
#include <cstdint>
#include <array>
namespace aoc::d6
{
	const char* inputPath = "day_six.txt";
	const int days = 256;

	std::vector<int> pufferFishInput = {};

	uint64_t calculate(std::vector<int>& input, int days)
	{
		// Create an array with slots for 9 (0-8) days + a sum buffer
		std::array<uint64_t, 10> daysBuffer{};

		uint64_t total = input.size();

		// Loop input
		for (const auto& input : input)
		{
			// Add into the next day buffer
			daysBuffer.at(input + 1)++;
		}

		// Now we can loop and sum over how many days using the overflow to give the answer
		for (int i = 0; i <= days; ++i)
		{
			// Store the first value temporary
			auto temporaryVal = daysBuffer.at(0);
			total += temporaryVal;

			daysBuffer[0] = daysBuffer[1];
			daysBuffer[1] = daysBuffer[2];
			daysBuffer[2] = daysBuffer[3];
			daysBuffer[3] = daysBuffer[4];
			daysBuffer[4] = daysBuffer[5];
			daysBuffer[5] = daysBuffer[6];
			// We add the temp value here as fish loop when they drop below 0 to 6
			daysBuffer[6] = daysBuffer[7] + temporaryVal;
			daysBuffer[7] = daysBuffer[8];
			// And here are the new fish
			daysBuffer[8] = temporaryVal;

		}
		return total;
	}

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
					pufferFishInput.push_back(std::stoi(numBuff));
					numBuff = "";
				}
				else
				{
					numBuff += digit;
				}
			}
		}

		// Last one
		pufferFishInput.push_back(std::stoi(numBuff));
		numBuff = "";

		std::cout << "Part 1: " << calculate(pufferFishInput, 80);
		

		std::cout << "Part 2: " << calculate(pufferFishInput, 256);

	}

	
}