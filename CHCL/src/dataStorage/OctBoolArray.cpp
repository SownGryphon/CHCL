#include "OctBoolArray.h"

#include <algorithm>
#include <cstring>

using namespace chcl;

OctBoolArray::OctBoolArray() :
	m_count{ 0 }, m_octBoolCount{ 0 }, m_data{ nullptr } {}

OctBoolArray::OctBoolArray(unsigned int size) :
	m_count{ size }, m_octBoolCount{ (size - 1) / 8 + 1 }
{
	m_data = new OctBool[m_count];
}

OctBoolArray::OctBoolArray(std::initializer_list<bool> list) :
	OctBoolArray(list.size())
{
	for (unsigned int i = 0; i < m_count; ++i)
	{
		set(i, *(list.begin() + i));
	}
}

OctBoolArray::OctBoolArray(const OctBoolArray &other) :
	OctBoolArray(other.m_count)
{
	for (unsigned int i = 0; i < m_octBoolCount; ++i)
	{
		m_data[i] = other.m_data[i];
	}
}

OctBoolArray::~OctBoolArray()
{
	delete[] m_data;
}

OctBoolArray& OctBoolArray::resize(unsigned int newCount)
{
	unsigned int newOctBoolCount = (newCount - 1) / 8 + 1;
	OctBool* newData = new OctBool[newOctBoolCount];
	std::memmove(newData, m_data, std::min(m_octBoolCount, newOctBoolCount));
	delete[] m_data;
	m_count = newCount;
	m_octBoolCount = newOctBoolCount;
	m_data = newData;

	return *this;
}

OctBoolArray& OctBoolArray::operator=(const OctBoolArray &other)
{
	if (m_octBoolCount != other.m_octBoolCount)
		resize(other.m_count);

	std::memcpy(m_data, other.m_data, m_octBoolCount);

	return *this;
}