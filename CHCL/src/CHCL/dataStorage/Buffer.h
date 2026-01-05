#pragma once

#include <cstdint>

namespace CHCL
{
	class Buffer
	{
	protected:
		uint8_t *m_data = nullptr;
		size_t m_size = 0, m_capacity = 0;

	public:
		Buffer() = default;
		Buffer(size_t presize);
		Buffer(const void *data, size_t size);
		Buffer(const Buffer &buffer);
		Buffer(Buffer &&buffer);

		~Buffer();

		void reserve(size_t size);
		void write(size_t index, const void *data, size_t size);
		void append(const void *data, size_t size);

		inline void* operator[](size_t index) { return m_data + index; }
		inline const void* operator[](size_t index) const { return m_data + index; }

		inline void* data() { return m_data; }
		inline const void* data() const { return m_data; }

		inline size_t size() const { return m_size; }

		explicit operator bool() const;

	private:

		void resize(size_t newSize, bool preserveContents = true);
	};
}