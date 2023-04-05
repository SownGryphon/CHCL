#include "include/OctBool.h"

using namespace chcl;

OctBool::OctBoolEntry::OctBoolEntry(OctBool &parent, const unsigned char index) :
	parent{ parent }, index{ index } {}

OctBool::OctBoolEntry::operator bool() const
{
	unsigned char bitIndex = 1 << index;

	return parent.data & bitIndex;
}

OctBool::OctBoolEntry& OctBool::OctBoolEntry::operator=(const bool state)
{
	unsigned char bitIndex = 1 << index;

	if (state)
	{
		parent.data |= bitIndex;
	}
	else
	{
		parent.data &= ~bitIndex;
	}

	return *this;
}

OctBool::OctBool(unsigned char data) :
	data{ data } {}

OctBool::OctBoolEntry OctBool::operator[](unsigned char index)
{
	return OctBoolEntry(*this, index);
}

OctBool::operator bool() const
{
	if (data)
		return true;
	else
		return false;
}