#include "day4.hpp"
#include <iostream>
#include <fstream>
#include <array>
#include <unordered_map>
#include "../../utility/funcs.hpp"
#include "../../utility/timer.hpp"

/*THOUGHTS: 
	This code is horrible lol, I'm not even going for nice code anymore. My approach to part 2 is particularly nasty
	I thought about removing boards from the list after the first win, which would be much faster, but there is just
	no point
*/


namespace aoc::d4
{
	const char* inputPath = "day_four.txt";

	struct boardValue
	{
		bool picked = false;
		int number = -1;
	};

	struct board
	{
		std::vector<std::vector<boardValue>> rows = {};
	};

	void execute()
	{
		utility::ScopeTimer myTimer;
		partOne();
		std::cout << "Part 1: " << myTimer.GetDeltaTime().GetMilliseconds() << "(ms)\n";
		partTwo();
		std::cout << "Part 2: " << myTimer.GetDeltaTime().GetMilliseconds() << "(ms)\n";
	}

	std::vector<int> orderOfDrawnNumbers = {};
	std::vector<board> boards = {};

	void partOne()
	{
		// Read input
		auto input = readFile(inputPath);

		// Turn into boards and values
		processInput(input);

		// Play game. We don't talk about this looping. If you think im gonna write optimal efficient code... no
		for (const auto& number : orderOfDrawnNumbers)
		{
			int boardIndex = 0;
			// Check each board for number, mark if hit
			for (auto& board : boards)
			{
				for (auto& row : board.rows)
				{
					for (auto& value : row)
					{
						if (value.number == number)
						{
							value.picked = true;
						}
					}
					// Check for row win cons
					int totalPicked = 0;
					for (auto& value : row)
					{
		
						if (value.picked)
						{
							totalPicked++;
						}
						if (totalPicked == row.size())
						{
							// This row has won break out.
							boardWon(boardIndex, number);
							return;
						}
					}
				}

				// Get length of col, boards are square so can just grab from length of first row
				const auto colLength = board.rows.at(0).size();

				// Loop 1 - 5
				for (int i = 0; i < colLength; ++i)
				{
					int totalPicked = 0;

					// Grab row, and check first value
					for (auto& row : board.rows)
					{
						// If picked
						if (row.at(i).picked)
						{
							totalPicked++;
						}
					}

					if (totalPicked == colLength)
					{
						// This row has won break out.
						boardWon(boardIndex, number);
						return;
					}
				}
				// Loop
				++boardIndex;
			}
			boardIndex = 0;

		}

	}

	void partTwo()
	{
		// Read input
		auto input = readFile(inputPath);

		// Turn into boards and values
		processInput(input);

		// Store board and when it won
		std::unordered_map<int, int> boardWins;

		// Play game. We don't talk about this looping. If you think im gonna write optimal efficient code... no
		for (const auto& number : orderOfDrawnNumbers)
		{
			int boardIndex = 0;
			// Check each board for number, mark if hit
			for (auto& board : boards)
			{
				for (auto& row : board.rows)
				{
					for (auto& value : row)
					{
						if (value.number == number)
						{
							value.picked = true;
						}
					}
					// Check for row win cons
					int totalPicked = 0;
					for (auto& value : row)
					{
						if (value.picked)
						{
							totalPicked++;
						}
						if (totalPicked == row.size())
						{
							// Just store the first time it wins
							if (!boardWins.contains(boardIndex))
							{
								boardWins[boardIndex] = number;
							}
							break;
						}
					}
				}

				// Get length of col, boards are square so can just grab from length of first row
				const auto colLength = board.rows.at(0).size();

				// Loop 1 - 5
				for (int i = 0; i < colLength; ++i)
				{
					int totalPicked = 0;

					// Grab row, and check first value
					for (auto& row : board.rows)
					{
						// If picked
						if (row.at(i).picked)
						{
							totalPicked++;
						}
					}
						
					if (totalPicked == colLength)
					{
						// Just store the first time it wins
						if (!boardWins.contains(boardIndex))
						{
							boardWins[boardIndex] = number;
						}
						break;
					}
				}

				// Loop
				++boardIndex;
			}
			if (boardWins.size() == boards.size())
			{
				break;
			}
			boardIndex = 0;
		}

		// Find last board
		auto last_elem = boardWins.begin();
		for (auto iter = boardWins.begin(); iter != boardWins.end(); iter++)
			last_elem = iter;
		// use last_elem, which now points to the last element in the map
		boardWon(last_elem->first, last_elem->second);
		return;
	}
	
	void processInput(std::vector<std::string>& input)
	{
		orderOfDrawnNumbers.clear();
		boards.clear();

		int stoppingPoint = 0;

		std::string numBuff = "";

		// First we need to get lines until we get a line that is doesn't contain commas. These lines with commas are orders
		for (const auto& line : input)
		{
			// If the line doesn't have a comma
			if (line.find(',') == line.npos)
			{
				// Break out the for loop
				break;
			}

			for (const auto& numOrComma : line)
			{
				if (numOrComma == ',')
				{
					orderOfDrawnNumbers.push_back(std::stoi(numBuff));
					numBuff = "";
					continue;
				}
				// Add value. This way we don't miss numbers that are 2 digits
				numBuff += numOrComma;
			}

			// Process the last one
			orderOfDrawnNumbers.push_back(std::stoi(numBuff));
			numBuff = "";

			// So we know where the boards start
			++stoppingPoint;
		}

		// Now we have the order of numbers. We need to process the boards
		board newBoard;
		int rowInBoard = 0;
		newBoard.rows.push_back({});
		for (int i = stoppingPoint + 1; i < input.size(); ++i)
		{
			const auto currentLine = input.at(i);
			// Inbetween boards
			if (currentLine.empty() && newBoard.rows.size() != 0)
			{
				// Might have added an empty row on the last line
				if (newBoard.rows.at(rowInBoard).size() == 0)
				{
					newBoard.rows.pop_back();
				}
				boards.push_back(newBoard);
				// Add the first row after reseting
				newBoard = {};
				newBoard.rows.push_back({});
				rowInBoard = 0;
				continue;
			}

			for (const auto& numOrSpace : currentLine)
			{
				// When hit space
				if (numOrSpace == ' ')
				{
					// Add new value
					if (numBuff != "")
					{
						newBoard.rows.at(rowInBoard).push_back({ false,std::stoi(numBuff) });
						numBuff = "";
					}
					continue;
				}

				numBuff += numOrSpace;

			}

			// Process the last one
			newBoard.rows.at(rowInBoard).push_back({ false,std::stoi(numBuff) });
			numBuff = "";

			// Add a new row
			newBoard.rows.push_back({});
			rowInBoard++;
		}

		// Push the last one
		if (newBoard.rows.at(rowInBoard).size() == 0)
		{
			newBoard.rows.pop_back();
		}
		boards.push_back(newBoard);

	}

	void boardWon(int indexOfWinningBoard, int lastPickedNum)
	{
		// get winning board
		const auto& winning = boards.at(indexOfWinningBoard);

		int unmarkedSum = 0;

		for (auto& row : winning.rows)
		{
			for (auto& value : row)
			{
				if (!value.picked)
				{
					unmarkedSum += value.number;
				}
			}
		}

		// Times and output
		std::cout << "Part 1: Board winning value: " << unmarkedSum * lastPickedNum << '\n';
	}

}
