#include "day2.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace aoc
{
	namespace d2
	{
		const char* inputPath = "day_two.txt";

		enum class direction
		{
			forward,
			down,
			up
		};

		struct instructionPair
		{
			direction direction;
			int value;
		};

		void execute()
		{
			// Open input text
			std::ifstream file;

			file.open(inputPath);
			if (file.fail())
			{
				std::cout << "Failed to open input file!";
				return;
			}

			std::string str;
			std::vector<std::string> inputLines;

			// Read lines
			while (std::getline(file, str))
			{
				inputLines.push_back(str);
			}
			file.close();

			// Loop lines 
			std::vector< instructionPair> movements;

			for (const auto& line : inputLines)
			{
				instructionPair newInstruction;

				// Find space between instruction and number
				auto splitIndex = line.find(' ');

				// Get direction
				auto directionStr = line.substr(0, splitIndex);
				if (directionStr == "forward")
				{
					newInstruction.direction = direction::forward;
				}
				else if (directionStr == "up")
				{
					newInstruction.direction = direction::up;
				}
				else
				{
					newInstruction.direction = direction::down;
				}

				// Get value
				auto valueStr = line.substr(splitIndex + 1, line.length());
				newInstruction.value = std::stoi(valueStr);

				movements.push_back(newInstruction);
			}

			// Loop instructions 
			int horizPosition = 0;
			int depth = 0;

			for (const auto& movement : movements)
			{
				switch (movement.direction)
				{
				case direction::forward:
					horizPosition += movement.value;
					break;
				case direction::up:
					depth -= movement.value;
					break;
				case direction::down:
					depth += movement.value;
					break;
				}
			}

			std::cout << "Day 2 Part 1: Final value: " << horizPosition * depth;

			// Now perform part 2
			horizPosition = 0;
			depth = 0;
			int aim = 0;

			for (const auto& movement : movements)
			{
				switch (movement.direction)
				{
				case direction::forward:
					horizPosition += movement.value;
					depth += movement.value * aim;
					break;
				case direction::up:
					aim -= movement.value;
					break;
				case direction::down:
					aim += movement.value;
					break;
				}
			}
			std::cout << "\nDay 2 Part 2: Final value: " << horizPosition * depth;
		}

	}
}