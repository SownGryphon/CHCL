#pragma once

#include <algorithm>
#include <vector>

namespace Asserts
{
	template <typename T>
	bool Equal(const T &t1, const T &t2)
	{
		return t1 == t2;
	}

	template <typename T>
	bool Equal(std::vector<T> t1, std::vector<T> t2)
	{
		std::sort(t1.begin(), t1.end());
		std::sort(t2.begin(), t2.end());
		return t1 == t2;
	}
}