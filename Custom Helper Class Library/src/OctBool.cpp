#include "include/OctBool.h"

using namespace chcl;

OctBool::OctBool() :
	data{ 0 } {}

OctBool::OctBool(unsigned char data) :
	data{ data } {}

const bool OctBool::operator[](unsigned char index) const
{
	return get(index);
}

const bool OctBool::get(unsigned char index) const
{
	unsigned char indexBit = 1 << index;

	return ((data & indexBit) >> index);
}

const bool OctBool::set(unsigned char index, const bool state)
{
	unsigned char indexBit = 1 << index;

	if (state)
		data |= indexBit;
	else
		data &= ~indexBit;

	return state;
}

OctBool::operator bool() const
{
	return data;
}