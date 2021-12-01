#pragma once
#include <unordered_map>

typedef void (*task_execute)(void);

#include "day_one/day1.hpp"
#include "day_two/day2.hpp"

namespace aoc
{
	const std::unordered_map<int, task_execute> EXECUTION_MAP {
		{1, executeDay1},
		{2, executeDay2}
	};

	const size_t MAX_DAYS = aoc::EXECUTION_MAP.size();
}