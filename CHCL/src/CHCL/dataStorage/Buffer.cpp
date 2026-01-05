#include "Buffer.h"

#include <cstring>

CHCL::Buffer::Buffer(size_t presize)
{
	resize(presize, false);
}

CHCL::Buffer::Buffer(const void *data, size_t presize) :
	Buffer(presize)
{
	append(data, presize);
}

CHCL::Buffer::Buffer(const Buffer &buffer) :
	Buffer(buffer.m_data, buffer.m_size)
{}

CHCL::Buffer::Buffer(Buffer &&buffer)
{
	m_data = buffer.m_data;
	m_size = buffer.m_size;
	m_capacity = buffer.m_capacity;

	buffer.m_data = nullptr;
	buffer.m_size = 0;
	buffer.m_capacity = 0;
}

CHCL::Buffer::~Buffer()
{
	if (*this)
	{
		delete[] m_data;
	}
}

void CHCL::Buffer::reserve(size_t size)
{
	if (size > m_size)
		resize(size, true);
}

void CHCL::Buffer::write(size_t index, const void *data, size_t size)
{
	std::memcpy(&m_data[index], data, size);
}

void CHCL::Buffer::append(const void *data, size_t size)
{
	write(m_size, data, size);
	m_size += size;
}

CHCL::Buffer::operator bool() const
{
	return m_capacity && m_data;
}

void CHCL::Buffer::resize(size_t newSize, bool preserveContents)
{
	uint8_t* newData = new uint8_t[newSize];

	if (preserveContents)
	{
		std::memcpy(newData, m_data, m_size);
	}

	delete[] m_data;
	m_data = newData;
	m_capacity = newSize;
}