#include "BitStream.h"

#include "BitStreamView.h"

void chcl::BitStream::pushBit(bool state)
{
	// Shift previous data to make space for new bit
	// This also handles increasing buffer size
	shift(1);

	// Write in the new bit of data
	if (state)
		m_data[0] |= 1;
}

void chcl::BitStream::pushBits(uint8_t *data, size_t numBits, uint8_t bitReadOffset)
{
	// Shift previous data to make space for new bits
	// This also handles increasing buffer size
	shift(numBits);

	BitStreamView dataView(data, bitReadOffset);
	dataView.readBits(m_data.data(), numBits);
}

bool chcl::BitStream::operator[](size_t i) const
{
	size_t byteIndex = (m_numBits - i - 1) / 8;
	size_t bitIndex = (m_numBits - i - 1) % 8;
	return m_data[byteIndex] & (1 << bitIndex);
}

void chcl::BitStream::shift(size_t bits)
{
	// Resize the data buffer if needed
	if (sizeBytes() < (m_numBits + bits + 7) / 8)
		m_data.resize((m_numBits + bits + 7) / 8);

	size_t shiftBytes = bits / 8;
	size_t shiftBits = bits % 8;
	uint8_t shiftBitMask = ~(0xff >> shiftBits);

	for (size_t i = m_data.size(); i--;)
	{
		// Only do calculations for bytes that have data shifted into them
		if (i >= shiftBytes)
		{
			m_data[i] = m_data[i - shiftBytes] << shiftBits;
			if (i > shiftBytes)
				m_data[i] |= (m_data[i - shiftBytes - 1] & shiftBitMask) >> (8 - shiftBits);
		}
		else
			m_data[i] = 0;
	}

	m_numBits += bits;
}

bool chcl::operator==(const BitStream &lhs, const BitStream &rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	for (size_t i = 0; i < lhs.sizeBytes(); ++i)
	{
		if (lhs.m_data[i] != rhs.m_data[i])
			return false;
	}
	return true;
}