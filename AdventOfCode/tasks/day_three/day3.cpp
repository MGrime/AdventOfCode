#include "day3.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <bitset>
#include <array>

#include "../../utility/funcs.hpp"
#include "../../utility/timer.hpp"

// It is important to note for todays thing that std::bitset stores numbers backwards from what you would expect. That is why the loop in part two is backwards.
// In part one, it didnt matter, as that could be done in reverse. However part two cannot be done in reverse as the array is manipulated, manipping in the
// reverse order yields a different answer.

namespace aoc
{
	namespace d3
	{
		constexpr int bitLength = 12;
		const char* inputPath = "day_three.txt";

		std::array<int, bitLength> mostCommonInBitSlot = std::array<int, bitLength>();

		void execute()
		{
			utility::ScopeTimer myTimer;
			partOne();
			std::cout << "Part 1: " << myTimer.GetDeltaTime().GetMilliseconds() << "(ms)\n";
			partTwo();
			std::cout << "Part 2: " << myTimer.GetDeltaTime().GetMilliseconds() << "(ms)\n";
		}

		void partOne()
		{
			const auto input = readFile(inputPath);

			// Store up to 12 bits per line
			std::vector<std::bitset<bitLength>> bitSets;

			// Loop and form bitset
			for (const auto& binaryStr : input)
			{
				bitSets.push_back(std::bitset<bitLength>(binaryStr));
			}

			// Create two bitsets to store the rates
			std::bitset<bitLength> gammaRate, epsilonRate;

			// Loop each bit to form numbers
			for (int i = 0; i < bitLength; ++i)
			{
				int amountOf0 = 0;
				int amountOf1 = 0;
				for (const auto& bitset : bitSets)
				{
					if (bitset[i] == 0)
					{
						amountOf0++;
					}
					else
					{
						amountOf1++;
					}
				}

				if (amountOf0 > amountOf1)
				{
					gammaRate[i] = 0;
					epsilonRate[i] = 1;
					mostCommonInBitSlot[i] = 0;
				}
				else
				{
					gammaRate[i] = 1;
					epsilonRate[i] = 0;
					mostCommonInBitSlot[i] = 1;
				}

			}

			auto gammaRateDec = gammaRate.to_ulong();
			auto epsilonRateDec = epsilonRate.to_ulong();

			std::cout << "Part 1: Rates multipled " << gammaRateDec * epsilonRateDec << '\n';
		}

		void partTwo()
		{
			const auto input = readFile(inputPath);

			// Store up to 12 bits per line
			std::vector<std::bitset<bitLength>> bitSets;

			// Loop and form bitset
			for (const auto& binaryStr : input)
			{
				bitSets.push_back(std::bitset<bitLength>(binaryStr));
			}

			// Process. Loop though bitsets and erase over and over leaving only ones that match the most common bit in that slot
			unsigned long oxygenRating = 0u;
			unsigned long co2Rating = 0u;

			// Create copies to be manipulated
			std::vector<std::bitset<bitLength>> bitsetsForOxygen = bitSets;
			std::vector<std::bitset<bitLength>> bitsetsForCO2 = bitSets;

			// Go backwards through the bitsets, because of the reason commented at the top
			for (int i = bitLength - 1; i >= 0; --i)
			{
				// Find the most common bit in the slot for remaining numbers
				// I wanted to cache this from part one, but it changes as you remove numbers
				int amountOf0 = 0;
				int amountOf1 = 0;
				int mostCommon;
				for (const auto& bitset : bitsetsForOxygen)
				{
					if (bitset[i] == 0)
					{
						amountOf0++;
					}
					else
					{
						amountOf1++;
					}
				}
				if (amountOf0 > amountOf1)
				{
					mostCommon = 0;
				}
				else
				{
					mostCommon = 1;
				}

				// Erase from our list if the bitset doesnt have the most common bit in this slot.
				std::erase_if(bitsetsForOxygen, [&](const std::bitset<bitLength> bitSet) {return !(bitSet[i] == mostCommon); });
				// Stop if we reach the last value
				if (bitsetsForOxygen.size() == 1)
				{
					break;
				}
			}

			// We can do this because we know 1 remains
			oxygenRating = bitsetsForOxygen[0].to_ulong();

			for (int i = bitLength - 1; i >= 0; --i)
			{
				// Find the most common bit in the slot for remaining numbers
				int amountOf0 = 0;
				int amountOf1 = 0;
				int mostCommon;
				for (const auto& bitset : bitsetsForCO2)
				{
					if (bitset[i] == 0)
					{
						amountOf0++;
					}
					else
					{
						amountOf1++;
					}
				}
				if (amountOf0 > amountOf1)
				{
					mostCommon = 0;
				}
				else
				{
					mostCommon = 1;
				}
				// Erase from our list if the bitset does have the most common bit in this slot.
				std::erase_if(bitsetsForCO2, [&](const std::bitset<bitLength> bitSet) {return !(bitSet[i] != mostCommon); });
				// Stop if we reach the last value
				if (bitsetsForCO2.size() == 1)
				{
					break;
				}
			}

			co2Rating = bitsetsForCO2[0].to_ulong();
			std::cout << "Part 2: Rates multipled " << oxygenRating * co2Rating << '\n';

		}
	}
}