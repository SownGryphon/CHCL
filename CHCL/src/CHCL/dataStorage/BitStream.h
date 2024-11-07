#pragma once

#include <vector>

namespace chcl
{
	class BitStream
	{
	public:
		BitStream() {}

		void pushBit(bool state);
		void pushBits(uint8_t *data, size_t numBits, uint8_t bitReadOffset);

		inline size_t size() const { return m_numBits; }
		inline size_t sizeBytes() const { return m_data.size(); }

		inline uint8_t* data() { return m_data.data(); }
		inline const uint8_t* data() const { return m_data.data(); }

		bool operator[](size_t i) const;

		friend bool operator==(const BitStream &lhs, const BitStream &rhs);

	private:
		size_t m_numBits = 0;
		std::vector<uint8_t> m_data;

		void shift(size_t bits);
	};
}