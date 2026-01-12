#include "BitStreamView.h"

#include <algorithm>

chcl::BitStreamView::BitStreamView(const uint8_t *begin, size_t size) :
	m_dataBegin(begin), m_size(size)
{}

chcl::BitStreamView::BitStreamView(const BitStream &stream) :
	BitStreamView(stream.data(), stream.size())
{}

bool chcl::BitStreamView::peekBit() const
{
	bool result = *(m_dataBegin + m_position / 8) & (0x1 << (m_position % 8));
	return result;
}

void chcl::BitStreamView::peekBits(uint8_t *dest, size_t numBits) const
{
	uint8_t offsetInByte = m_position % 8;
	uint8_t upperBitMask = 0xff << offsetInByte;
	for (size_t i = 0; i < numBits / 8; ++i)
	{
		// Read what is necessary from the i-th byte
		uint8_t newByte = (*(m_dataBegin + m_position / 8 + i) & upperBitMask);

		// If reading across byte boundaries, read from the next byte and combine with previous value
		if (offsetInByte != 0)
			newByte = (newByte >> offsetInByte) | ((*(m_dataBegin + m_position / 8 + i + 1) & ~upperBitMask) << (8 - offsetInByte));
		
		dest[i] = newByte;
	}

	// Number of bits to write into the next byte of the stream
	uint8_t numLeftoverBits = numBits % 8;
	if (numLeftoverBits)
	{
		// How many of the leftover bits are in the upper bits of the most recently read byte
		uint8_t bitsLeftoverUpper = std::min<uint8_t>((8 - offsetInByte) % 8, numLeftoverBits);
		uint8_t partByte = (*(m_dataBegin + m_position / 8 + numBits / 8) & upperBitMask) >> offsetInByte;
		if (bitsLeftoverUpper < numLeftoverBits)
		{
			partByte |= (*(m_dataBegin + m_position / 8 + numBits / 8 + 1) & ~upperBitMask) << bitsLeftoverUpper;
		}
		partByte &= ~(0xff << numLeftoverBits);
		dest[numBits / 8] |= partByte;
	}
}


bool chcl::BitStreamView::readBit()
{
	// ProfileScope(readBit)
	bool result = peekBit();
	jump(1);
	return result;
}

void chcl::BitStreamView::readBits(uint8_t *dest, size_t numBits)
{
	peekBits(dest, numBits);
	jump(numBits);
}

std::ostream& chcl::operator<<(std::ostream &ostream, const chcl::BitStreamView &view)
{
	BitStreamView ref{ view };
	while (!ref.eof())
	{
		ostream << ref.readBit();
	}
	return ostream;
}