#include "include/OctBoolArray.h"

#include <algorithm>
#include <cstring>

using namespace chcl;

OctBoolArray::OctBoolArray() :
	size{ 0 }, numElements{ 0 }, data{ nullptr } {}

OctBoolArray::OctBoolArray(unsigned int size) :
	size{ size }, numElements{ (size - 1) / 8 + 1 }
{
	data = new OctBool[numElements];
}

OctBoolArray::OctBoolArray(const OctBoolArray& other) :
	OctBoolArray{ other.size }
{
	for (unsigned int i = 0; i < numElements; ++i)
	{
		data[i] = other.data[i];
	}
}

OctBoolArray::~OctBoolArray()
{
	delete[] data;
}

OctBoolArray& OctBoolArray::resize(unsigned int newSize)
{
	unsigned int newNumElements = (newSize - 1) / 8 + 1;
	OctBool* newData = new OctBool[newNumElements];
	std::memmove(newData, data, std::min(numElements, newNumElements));
	delete[] data;
	numElements = newNumElements;
	data = newData;

	return *this;
}

OctBoolArray& OctBoolArray::operator=(const OctBoolArray& other)
{
	if (numElements != other.numElements)
		resize(other.size);

	std::memcpy(data, other.data, numElements);

	return *this;
}

inline const bool OctBoolArray::operator[](unsigned int index) const
{
	return get(index);
}

inline const bool OctBoolArray::get(unsigned int index) const
{
	return data[index >> 3].get(index & 0b111);
}

inline const bool OctBoolArray::set(unsigned int index, const bool state)
{
	return data[index >> 3].set(index & 0b111, state);
}