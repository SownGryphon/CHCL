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

		OctBoolArray& resize(unsigned int newSize);

		OctBoolArray& operator=(const OctBoolArray& other);
		inline const bool operator[](unsigned int index) const;

		inline const bool get(unsigned int index) const;
		inline const bool set(unsigned int index, const bool state);
	private:
		unsigned int count, octBoolCount;
		OctBool* data;
	};
}