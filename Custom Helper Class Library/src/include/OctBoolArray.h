#pragma once

#include "OctBool.h"

namespace chcl
{
	class OctBoolArray
	{
	public:
		OctBoolArray();
		OctBoolArray(unsigned int size);
		OctBoolArray(const OctBoolArray& other);
		~OctBoolArray();

		OctBoolArray& resize(unsigned int newSize);

		OctBoolArray& operator=(const OctBoolArray& other);
		inline const bool operator[](unsigned int index) const;

		inline const bool get(unsigned int index) const;
		inline const bool set(unsigned int index, const bool state);
	private:
		unsigned int size, numElements;
		OctBool* data;
	};
}