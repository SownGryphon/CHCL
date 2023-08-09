#include "OctBoolArray.h"

#include <algorithm>
#include <cstring>

using namespace chcl;

OctBoolArray::OctBoolArray() :
	count{ 0 }, octBoolCount{ 0 }, data{ nullptr } {}

OctBoolArray::OctBoolArray(unsigned int size) :
	count{ size }, octBoolCount{ (size - 1) / 8 + 1 }
{
	data = new OctBool[count];
}

OctBoolArray::OctBoolArray(std::initializer_list<bool> list) :
	OctBoolArray(list.size())
{
	for (unsigned int i = 0; i < count; ++i)
	{
		set(i, *(list.begin() + i));
	}
}

OctBoolArray::OctBoolArray(const OctBoolArray& other) :
	OctBoolArray(other.count)
{
	for (unsigned int i = 0; i < octBoolCount; ++i)
	{
		data[i] = other.data[i];
	}
}

OctBoolArray::~OctBoolArray()
{
	delete[] data;
}

OctBoolArray& OctBoolArray::resize(unsigned int newCount)
{
	unsigned int newOctBoolCount = (newCount - 1) / 8 + 1;
	OctBool* newData = new OctBool[newOctBoolCount];
	std::memmove(newData, data, std::min(octBoolCount, newOctBoolCount));
	delete[] data;
	count = newCount;
	octBoolCount = newOctBoolCount;
	data = newData;

	return *this;
}

OctBoolArray& OctBoolArray::operator=(const OctBoolArray& other)
{
	if (octBoolCount != other.octBoolCount)
		resize(other.count);

	std::memcpy(data, other.data, octBoolCount);

	return *this;
}