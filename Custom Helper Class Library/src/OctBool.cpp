#include "OctBool.h"

using namespace chcl;

OctBool::OctBool() :
	m_data{ 0 } {}

OctBool::OctBool(unsigned char data) :
	m_data{ data } {}

const bool OctBool::set(unsigned char index, const bool state)
{
	unsigned char indexBit = 1 << index;

	if (state)
		m_data |= indexBit;
	else
		m_data &= ~indexBit;

	return state;
}

OctBool::operator bool() const
{
	return m_data;
}