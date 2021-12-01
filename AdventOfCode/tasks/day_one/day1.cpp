#include "day1.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace aoc
{
	namespace d1
	{
		const char* inputPath = "day_one.txt";

		void partOne()
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
			std::vector<int> inputNumbers;

			// Read lines
			while (std::getline(file, str))
			{
				int inputNum = std::stoi(str);
				inputNumbers.push_back(inputNum);
			}
			file.close();
			// Loop lines

			// First number
			int prevNum = inputNumbers.at(0);

			// Number bigger
			int numBigger = 0;

			for (int i = 1; i < inputNumbers.size(); ++i)
			{
				// Get curr num
				int currNum = inputNumbers.at(i);

				// Check
				if (currNum > prevNum)
				{
					numBigger++;
				}

				// Store this as previous
				prevNum = currNum;
			}

			// Output
			std::cout << "Part 1: Amount of measurements bigger: " << numBigger << '\n';
		}

		void partTwo()
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
			std::vector<int> inputNumbers;

			// Read lines
			while (std::getline(file, str))
			{
				int inputNum = std::stoi(str);
				inputNumbers.push_back(inputNum);
			}
			file.close();
			// Loop
			int numBigger = 0;

			int prevSum = inputNumbers.at(0) + inputNumbers.at(1) + inputNumbers.at(2);

			for (int i = 1; i < inputNumbers.size(); ++i)
			{
				int currSum = inputNumbers.at(i);
				if (i + 1 < inputNumbers.size())
				{
					currSum += inputNumbers.at(i + 1);
				}
				if (i + 2 < inputNumbers.size())
				{
					currSum += inputNumbers.at(i + 2);
				}

				if (currSum > prevSum)
				{
					numBigger++;
				}

				prevSum = currSum;
			}

			// Output
			std::cout << "Part 2: Amount of measurements bigger: " << numBigger << '\n';

		}

		void execute()
		{
			partOne();
			partTwo();
		}
	}
}