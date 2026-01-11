#pragma once

#include <cstdint>

namespace chcl
{
	/**
	 * Class for reading individual bits from a block of data
	 * Iterates through bytes in ascending address order, through bits from least to most significant 
	 * */
	class BitStreamView
	{
	public:
		/**
		 * Create a BitStreamView to read bit data starting from a certain bit
		 * 
		 * @param begin Pointer to first data byte
		 * @param bitOffset Starting offset to read from, in bits
		 */
		BitStreamView(const uint8_t* begin, uint8_t bitOffset = 0);

		/**
		 * Read the next bit value
		 * Does not advance the read position
		 * @returns The value of the next bit
		 */
		bool peekBit() const;
		/**
		 * Read some number of bits into a buffer
		 * Does not advance the read position
		 * 
		 * Read data is packed in the same order as it is read: bit from least to most significant, bytes in ascending address order
		 * 
		 * @param dest Pointer to buffer to place data.
		 * 	Must be at least ceil(numBits/8) bytes
		 * @param numBits Number of bits to read into dest
		 */
		void peekBits(uint8_t *dest, size_t numBits) const;

		/**
		 * Read the value of the next bit
		 * Same as peekBit() but advances the read position by 1 bit
		 * @returns Value of the next bit
		 */
		bool readBit();
		/**
		 * Read a number of bits to a buffer
		 * Same as peekBits(uint8_t*,size_t) but advances the read position by numBits
		 */
		void readBits(uint8_t *dest, size_t numBits);

		/**
		 * Reads some data and returns it in an integer
		 * See readBits(uint8_t*,size_t) for specifics
		 * 
		 * @param numBits Number of bits to read
		 * @returns Integer containing read data
		 */
		template <typename T = uint8_t>
		T readBits(size_t numBits)
		{
			T result = 0;
			readBits((uint8_t*)&result, numBits);
			return result;
		}

		/**
		 * Reads some data and returns it in an integer
		 * See readBits(uint8_t*,size_t) for specifics
		 * 
		 * @param numBits Number of bits to read
		 * @returns Integer containing read data
		 */
		template <typename T = uint8_t>
		T peekBits(size_t numBits) const
		{
			T result = 0;
			peekBits((uint8_t*)&result, numBits);
			return result;
		}

		/**
		 * Move the read position to the given position
		 * @param bitPos Bit offset from the start of the data to place read position at
		 */
		inline void seek(size_t bitPos) { m_bitOffset = bitPos; }
		/** Move the read position forward by 'bits' */
		inline void jump(size_t bits) { m_bitOffset += bits; }
		/// @brief Move the read position to the next byte boundary
		inline void skipTrailingBits() { jump((8 - m_bitOffset) % 8); }

		inline const uint8_t* readPos() const { return m_dataBegin + m_bitOffset % 8; }

	private:
		const uint8_t *m_dataBegin;
		size_t m_bitOffset;
	};
}