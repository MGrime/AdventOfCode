#pragma once
#include <string>
#include <vector>
namespace aoc
{
	namespace d4
	{
		void execute();
		void partOne();
		void partTwo();
		void processInput(std::vector<std::string>& input);
		void boardWon(int indexOfWinningBoard, int lastPickedNum);
	}
}