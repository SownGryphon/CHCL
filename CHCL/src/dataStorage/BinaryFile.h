#pragma once

#include <fstream>
#include <string>

namespace chcl
{
	enum class Endianness
	{
		Big, Little,
		Default
	};

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
			if (endian == Endianness::Little)
				std::ifstream::read((char*)&result, sizeof(T));
			else if (endian == Endianness::Big)
			{
				for (size_t i = 0; i < sizeof(T); ++i)
				{
					std::ifstream::read((char*)&result + sizeof(T) - i - 1, 1);
				}
			}

			return result;
		}

	private:

		Endianness m_defaultEndian;
	};
}