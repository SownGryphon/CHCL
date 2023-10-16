#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace Asserts
{
	template <typename T>
	bool Equal(const T &t1, const T &t2, const std::string &failText = "Failed equality assert.\n")
	{
		if (t1 == t2)
			return true;

		std::cout << failText;
		__debugbreak();
		return false;
	}

	template <typename T>
	bool Equal(std::vector<T> t1, std::vector<T> t2, const std::string &failText = "Failed equality assert.\n")
	{
		std::sort(t1.begin(), t1.end());
		std::sort(t2.begin(), t2.end());

		if (t1 == t2)
			return true;

		std::cout << failText;
		__debugbreak();
		return false;
	}

	template <typename T>
	bool NotEqual(const T &t1, const T &t2, const std::string &failText = "Failed inequality assert.\n")
	{
		if (t1 != t2)
			return true;

		std::cout << failText;
		__debugbreak();
		return false;
	}
}