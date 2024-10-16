#include "BitStreamView.h"

#include <algorithm>

chcl::BitStreamView::BitStreamView(const uint8_t *begin, uint8_t offset) :
	m_dataBegin(begin), m_bitOffset(offset)
{}

bool chcl::BitStreamView::readBit()
{
	bool result = *(m_dataBegin + m_bitOffset / 8) & (1 << (m_bitOffset % 8));
	jump(1);
	return result;
}

void chcl::BitStreamView::readBits(uint8_t *dest, size_t numBits)
{
	uint8_t upperBitMask = 0xff << (m_bitOffset % 8);
	for (size_t i = 0; i < numBits / 8; ++i)
	{
		uint8_t newByte = ((*(m_dataBegin + m_bitOffset / 8 + i) & upperBitMask) >> (m_bitOffset % 8)) | ((*(m_dataBegin + m_bitOffset / 8 + i + 1) & ~upperBitMask) << (8 - (m_bitOffset % 8)));
		dest[i] = newByte;
	}

	// Number of bits to write into the next byte of the stream
	uint8_t numLeftoverBits = numBits % 8;
	if (numLeftoverBits)
	{
		// How many of the leftover bits are in the upper bits of the most recently read byte
		uint8_t bitsLeftoverUpper = std::min<uint8_t>((8 - (m_bitOffset % 8)) % 8, numLeftoverBits);
		uint8_t partByte = (*(m_dataBegin + m_bitOffset / 8 + numBits / 8) & upperBitMask) >> (m_bitOffset % 8);
		if (bitsLeftoverUpper < numLeftoverBits)
		{
			partByte |= (*(m_dataBegin + m_bitOffset / 8 + numBits / 8 + 1) & ~upperBitMask) << bitsLeftoverUpper;
		}
		partByte &= ~(0xff << numLeftoverBits);
		dest[numBits / 8] |= partByte;
	}

	jump(numBits);
}
