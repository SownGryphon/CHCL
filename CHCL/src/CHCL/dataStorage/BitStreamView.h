#pragma once

#include <cstdint>

namespace chcl
{
	class BitStreamView
	{
	public:
		BitStreamView(const uint8_t* begin, uint8_t bitOffset);

		bool readBit();
		void readBits(uint8_t *dest, size_t numBits);

		template <typename T = uint8_t>
		T readBits(size_t numBits)
		{
			T result = 0;
			readBits((uint8_t*)&result, numBits);
			return result;
		}

		inline void seek(size_t bitPos) { m_bitOffset = bitPos; }
		inline void jump(size_t bits) { m_bitOffset += bits; }
		inline void skipTrailingBits() { jump((8 - m_bitOffset) % 8); }

		inline const uint8_t* getPos() const { return m_dataBegin; }

	private:
		const uint8_t *m_dataBegin;
		size_t m_bitOffset;
	};
}