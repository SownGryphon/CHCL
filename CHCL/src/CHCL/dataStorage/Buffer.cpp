#include "Buffer.h"

#include <cstring>
#include <utility>

#include "CHCL/misc/Profiler.h"

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
	clear();
}

void chcl::Buffer::reserve(size_t size)
{
	if (size > m_capacity)
		resize(size, true);
}

void chcl::Buffer::write(size_t index, const void *data, size_t size)
{
	if (index + size > m_capacity)
		expand(index + size);

	std::memcpy(&m_data[index], data, size);

	if (index + size > m_size)
		m_size = index + size;
}

void chcl::Buffer::append(const void *data, size_t size)
{
	write(m_size, data, size);
}

void chcl::Buffer::clear()
{
	if (m_data)
		delete[] m_data;

	m_size = 0;
	m_capacity = 0;
	m_data = nullptr;
}

chcl::Buffer::operator bool() const
{
	return m_size && m_data && m_capacity;
}

chcl::Buffer& chcl::Buffer::operator=(const Buffer &other)
{
	resize(other.size(), false);
	append(other.data(), other.size());
	return *this;
}

chcl::Buffer& chcl::Buffer::operator=(Buffer &&other)
{
	clear();

	m_data = other.m_data;
	m_size = other.m_size;
	m_capacity = other.m_capacity;

	other.m_data = nullptr;
	other.m_size = 0;
	other.m_capacity = 0;

	return *this;
}

void chcl::Buffer::resize(size_t newSize, bool preserveContents)
{
	uint8_t* newData = new uint8_t[newSize];

	if (preserveContents)
	{
		std::memcpy(newData, m_data, m_size);
	}
	else
		m_size = 0;

	if (m_data)
		delete[] m_data;
	
	m_data = newData;
	m_capacity = newSize;
}

void chcl::Buffer::expand(size_t minsize)
{
	size_t predictiveSize = m_size * 2;

	resize(std::max(minsize, predictiveSize), true);
}