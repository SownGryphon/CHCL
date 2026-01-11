#pragma once

#include <fstream>
#include <string>

#include "NetworkOrder.h"

namespace chcl
{
	class BinaryFile : public std::ifstream
	{
	public:
		BinaryFile(const std::string &filename, Endianness defaultEndian);

		template <typename T> requires std::is_integral<T>::value
		T readInt(Endianness endian = Endianness::Default)
		{
			if (endian == Endianness::Default)
				endian = m_defaultEndian;

			T result = 0;
			std::ifstream::read((char*)&result, sizeof(T));
			if (endian == Endianness::Big)
			{
				return NetworkOrder::reverse(&result);
			}

			return result;
		}

	private:

		Endianness m_defaultEndian;
	};
}