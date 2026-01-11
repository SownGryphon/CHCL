#pragma once

#include <istream>

namespace chcl
{
	enum class Endianness
	{
		Big, Little,
		Default
	};

	namespace NetworkOrder
	{
		template <typename T> requires std::is_integral<T>::value
		T reverse(T *value)
		{
			T result = 0;

			for (size_t i = 0; i < sizeof(T); ++i)
			{
				std::memcpy(((uint8_t*)&result) + i, ((uint8_t*)value) + sizeof(T) - i - 1, 1);
			}

			return result;
		}
	};
}