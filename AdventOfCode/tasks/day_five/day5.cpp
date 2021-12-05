#include "day5.hpp"
#include <iostream>
#include <fstream>
#include <array>
#include <unordered_map>
#include <vector>
#include <string>
#include "../../utility/funcs.hpp"
#include "../../utility/timer.hpp"

namespace aoc::d5
{
	struct vec2
	{
		int x;
		int y;

		bool operator==(const vec2& other) const
		{
			return (x == other.x
				&& y == other.y);
		}
	};
}

namespace std {

	template <>
	struct hash< aoc::d5::vec2>
	{
		std::size_t operator()(const aoc::d5::vec2& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<string>()(std::to_string(k.x))
				^ (hash<string>()(std::to_string(k.y)) << 1)) >> 1);
		}
	};

}

namespace aoc::d5
{
	const char* inputPath = "day_five.txt";
	void execute()
	{
		partOne();
	}

	struct line
	{
		vec2 start;
		vec2 end;
	};

	std::vector<line> lines = std::vector<line>();

	std::unordered_map<vec2, int> overlapGrid = {};

	void partOne()
	{
		// Read input
		auto input = readFile(inputPath);

		std::string numBuff = "";

		for (const auto& str : input)
		{
			line newLine;
			int numCounter = 0;
			for (const auto& digit : str)
			{
				if (digit != '>' && digit != ' ')
				{
					if ((digit == ',' || digit == '-') && numBuff != "")
					{
						switch (numCounter)
						{
						case 0:
							newLine.start.x = std::stoi(numBuff);
							numBuff = "";
							numCounter++;
							break;
						case 1:
							newLine.start.y = std::stoi(numBuff);
							numBuff = "";
							numCounter++;
							break;
						case 2:
							newLine.end.x = std::stoi(numBuff);
							numBuff = "";
							numCounter++;
							break;
						}
					}
					else
					{
						numBuff += digit;
					}			
				}
			}
			newLine.end.y = std::stoi(numBuff);
			numBuff = "";
			lines.push_back(newLine);
		}

		for (const auto& line : lines)
		{
			// Only consider horiz or vertical
			if (line.start.x == line.end.x)
			{
				// check y changes
				int yDir = line.start.y - line.end.y;

				if (yDir < 0)
				{
					for (int y = line.start.y; y <= line.end.y; ++y)
					{
						vec2 currPoint = { line.start.x, y };
						if (overlapGrid.contains(currPoint))
						{
							overlapGrid[currPoint]++;
						}
						else
						{
							overlapGrid[currPoint] = 1;
						}

					}
				}
				else
				{
					for (int y = line.start.y; y >= line.end.y; --y)
					{
						vec2 currPoint = { line.start.x, y };
						if (overlapGrid.contains(currPoint))
						{
							overlapGrid[currPoint]++;
						}
						else
						{
							overlapGrid[currPoint] = 1;
						}
					}
				}
			}
			else if (line.start.y == line.end.y)
			{
				// check x changes
				int xDir = line.start.x - line.end.x;

				if (xDir < 0)
				{
					for (int x = line.start.x; x <= line.end.x; ++x)
					{
						vec2 currPoint = { x, line.start.y };
						if (overlapGrid.contains(currPoint))
						{
							overlapGrid[currPoint]++;
						}
						else
						{
							overlapGrid[currPoint] = 1;
						}

					}
				}
				else
				{
					for (int x = line.start.x; x >= line.end.x; --x)
					{
						vec2 currPoint = { x, line.start.y };
						if (overlapGrid.contains(currPoint))
						{
							overlapGrid[currPoint]++;
						}
						else
						{
							overlapGrid[currPoint] = 1;
						}
					}
				}
			}
			// diagonal. This is basically part 2. Remove this and you get the part 1 answer
			else
			{
				int xDir = (line.start.x - line.end.x);
				int yDir = (line.start.y - line.end.y);

				vec2 currPoint;
				// Diagonally down left
				if (xDir > 0 && yDir > 0)
				{
					for (int x = line.start.x, y = line.start.y; x >= line.end.x, y >= line.end.y; --x, --y)
					{
						currPoint = { x, y };
						if (overlapGrid.contains(currPoint))
						{
							overlapGrid[currPoint]++;
						}
						else
						{
							overlapGrid[currPoint] = 1;
						}
					}
				}
				// Digonally down right
				else if (xDir < 0 && yDir > 0)
				{
					for (int x = line.start.x, y = line.start.y; x <= line.end.x, y >= line.end.y; ++x, --y)
					{
						currPoint = { x, y };
						if (overlapGrid.contains(currPoint))
						{
							overlapGrid[currPoint]++;
						}
						else
						{
							overlapGrid[currPoint] = 1;
						}
					}
				}
				// Digonally up right
				else if (xDir < 0 && yDir < 0)
				{
					for (int x = line.start.x, y = line.start.y; x <= line.end.x, y <= line.end.y; ++x, ++y)
					{
						currPoint = { x, y };
						if (overlapGrid.contains(currPoint))
						{
							overlapGrid[currPoint]++;
						}
						else
						{
							overlapGrid[currPoint] = 1;
						}
					}
				}
				// Digonally up left
				else
				{
					for (int x = line.start.x, y = line.start.y; x >= line.end.x, y <= line.end.y; --x, ++y)
					{
						currPoint = { x, y };
						if (overlapGrid.contains(currPoint))
						{
							overlapGrid[currPoint]++;
						}
						else
						{
							overlapGrid[currPoint] = 1;
						}
					}
				}

			}
		}

		// Now loop overlaps
		int overLapAmount = 0;
		for (const auto& overlap : overlapGrid)
		{
			if (overlap.second >= 2)
			{
				overLapAmount++;
			}
		}

		std::cout << "Part 2 : 2 or more Overlaps: " << overLapAmount << '\n';
	}

}