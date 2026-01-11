#pragma once

#include <cstdint>

namespace chcl
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

		template <typename T>
		void append(const T &value)
		{
			append(&value, sizeof(T));
		}
		template <typename T>
		void write(size_t index, const T &value)
		{
			write(index, &value, sizeof(T));
		}

		void clear();

		inline void* data() { return m_data; }
		inline const void* data() const { return m_data; }
		inline const void* end() const { return m_data + m_size; }

		inline void setSize(size_t newSize) { m_size = newSize; }

		inline size_t size() const { return m_size; }
		inline size_t capacity() const { return m_capacity; }

		inline void* operator[](size_t index) { return m_data + index; }
		inline const void* operator[](size_t index) const { return m_data + index; }

		explicit operator bool() const;

		Buffer& operator=(const Buffer &other);
		Buffer& operator=(Buffer &&other);

	private:

		void resize(size_t newSize, bool preserveContents = true);
		void expand(size_t minsize);
	};
}