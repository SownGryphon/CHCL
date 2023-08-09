#pragma once

#include <initializer_list>

#include "OctBool.h"

namespace chcl
{
	class OctBoolArray
	{
	public:
		OctBoolArray();
		OctBoolArray(unsigned int size);
		OctBoolArray(std::initializer_list<bool> list);
		OctBoolArray(const OctBoolArray& other);
		~OctBoolArray();

		OctBoolArray& resize(unsigned int newCount);

		OctBoolArray& operator=(const OctBoolArray& other);
		inline const bool operator[](unsigned int index) const { return get(index); }

		inline const bool get(unsigned int index) const { return data[index >> 3].get(index & 0b111); }
		inline const bool set(unsigned int index, const bool state) { return data[index >> 3].set(index & 0b111, state); }
	private:
		unsigned int count, octBoolCount;
		OctBool* data;
	};
}