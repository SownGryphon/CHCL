#include "OctBool.h"

using namespace chcl;

OctBool::OctBool() :
	data{ 0 } {}

OctBool::OctBool(unsigned char data) :
	data{ data } {}

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