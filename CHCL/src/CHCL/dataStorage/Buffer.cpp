#include "Buffer.h"

#include <cstring>
#include <utility>

chcl::Buffer::Buffer(size_t presize)
{
	resize(presize, false);
}

chcl::Buffer::Buffer(const void *data, size_t presize) :
	Buffer(presize)
{
	append(data, presize);
}

chcl::Buffer::Buffer(const Buffer &buffer) :
	Buffer(buffer.m_data, buffer.m_size)
{}

chcl::Buffer::Buffer(Buffer &&buffer)
{
	*this = std::move(buffer);
}

chcl::Buffer::~Buffer()
{
	if (*this)
	{
		delete[] m_data;
	}
}

void chcl::Buffer::reserve(size_t size)
{
	if (size > m_size)
		resize(size, true);
}

void chcl::Buffer::write(size_t index, const void *data, size_t size)
{
	std::memcpy(&m_data[index], data, size);
}

void chcl::Buffer::append(const void *data, size_t size)
{
	write(m_size, data, size);
	m_size += size;
}

chcl::Buffer::operator bool() const
{
	return m_size && m_data;
}

chcl::Buffer& chcl::Buffer::operator=(const Buffer &other)
{
	resize(other.size(), false);
	append(other.data(), other.size());
	return *this;
}

chcl::Buffer& chcl::Buffer::operator=(Buffer &&other)
{
	if (*this)
		delete[] m_data;

	m_data = other.m_data;
	m_size = other.m_size;

	other.m_data = nullptr;
	other.m_size = 0;

	return *this;
}

void chcl::Buffer::resize(size_t newSize, bool preserveContents)
{
	uint8_t* newData = new uint8_t[newSize];

	if (preserveContents)
	{
		std::memcpy(newData, m_data, m_size);
	}

	if (*this)
		delete[] m_data;
	
	m_data = newData;
	m_size = newSize;
}