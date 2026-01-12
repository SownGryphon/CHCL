#pragma once

#include <vector>

namespace chcl
{
	class BitStream
	{
	private:
		size_t m_sizeBits = 0; ///< Size of data, in bits
		std::vector<uint8_t> m_data; ///< Buffer for storing data

	public:
		BitStream() {}

		void pushBit(bool state);
		void pushBits(uint8_t *data, size_t numBits, uint8_t bitReadOffset);
		void appendBit(bool state);

		inline size_t size() const { return m_sizeBits; }
		inline size_t sizeBytes() const { return m_data.size(); }

		inline uint8_t* data() { return m_data.data(); }
		inline const uint8_t* data() const { return m_data.data(); }

		bool operator[](size_t i) const;

		friend bool operator==(const BitStream &lhs, const BitStream &rhs);

	private:
		void shift(size_t bits);
	};
}