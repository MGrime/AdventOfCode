#pragma once
#include <unordered_map>

typedef void (*task_execute)(void);

#include "day_one/day1.hpp"
#include "day_two/day2.hpp"
#include "day_three/day3.hpp"
#include "day_four/day4.hpp"
#include "day_five/day5.hpp"
#include "day_six/day6.hpp"
#include "day_seven/day7.hpp"

namespace aoc
{
	const std::unordered_map<int, task_execute> EXECUTION_MAP {
		{1, d1::execute},
		{2, d2::execute},
		{3, d3::execute},
		{4, d4::execute},
		{5, d5::execute},
		{6, d6::execute},
		{7, d7::execute}
	};

	const size_t MAX_DAYS = aoc::EXECUTION_MAP.size();
}