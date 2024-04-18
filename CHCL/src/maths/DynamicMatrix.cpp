#include "DynamicMatrix.h"

#include <stdexcept>

chcl::DynamicMatrix::DynamicMatrix() :
	m_width(0), m_height(0)
{}

chcl::DynamicMatrix::DynamicMatrix(unsigned int width, unsigned int height, float defaultVal) :
	m_width(width), m_height(height)
{
	m_elements.resize(size_t(width) * height, defaultVal);
}

chcl::DynamicMatrix::DynamicMatrix(unsigned int width, unsigned int height, const std::vector<float> &values)
{
	if (values.size() != size_t(width) * height) throw std::invalid_argument("Invalid vector size for intializing matrix.");

	m_width = width;
	m_height = height;
	m_elements = values;
}

chcl::DynamicMatrix::DynamicMatrix(const DynamicMatrix &other) :
	m_width(other.m_width), m_height(other.m_height),
	m_elements(other.m_elements)
{}

chcl::DynamicMatrix::DynamicMatrix(DynamicMatrix &&other) :
	m_width(other.m_width), m_height(other.m_height)
{
	m_elements = std::move(other.m_elements);
	other.m_width = 0;
	other.m_height = 0;
}

float& chcl::DynamicMatrix::at(unsigned int row, unsigned int col)
{
	if (row > m_height || col > m_width) throw std::out_of_range("Matrix access location out of range.");

	return m_elements[size_t(row) * m_width + col];
}

const float& chcl::DynamicMatrix::at(unsigned int row, unsigned int col) const
{
	if (row > m_height || col > m_width) throw std::out_of_range("Matrix access location out of range.");

	return m_elements[size_t(row) * m_width + col];
}

chcl::DynamicMatrix& chcl::DynamicMatrix::operator=(const DynamicMatrix &other)
{
	if (other.getSize() != getSize()) resize(other.getSize());

	for (unsigned int i = 0; i < m_height; ++i)
	{
		for (unsigned int j = 0; j < m_width; ++j)
		{
			at(i, j) = other.at(i, j);
		}
	}

	return *this;
}

chcl::DynamicMatrix& chcl::DynamicMatrix::operator+=(const DynamicMatrix &other)
{
	if (other.getSize() != getSize()) throw std::invalid_argument("Matrix sizes do not match for addition.");

	for (unsigned int i = 0; i < m_height; ++i)
	{
		for (unsigned int j = 0; j < m_width; ++j)
		{
			at(i, j) += other.at(i, j);
		}
	}

	return *this;
}

chcl::DynamicMatrix& chcl::DynamicMatrix::operator-=(const DynamicMatrix &other)
{
	if (other.getSize() != getSize()) throw std::invalid_argument("Matrix sizes do not match for subtraction.");

	for (unsigned int i = 0; i < m_height; ++i)
	{
		for (unsigned int j = 0; j < m_width; ++j)
		{
			at(i, j) -= other.at(i, j);
		}
	}

	return *this;
}

chcl::DynamicMatrix& chcl::DynamicMatrix::operator*=(const DynamicMatrix &other)
{
	*this = *this * other;

	return *this;
}

chcl::DynamicMatrix chcl::operator+(DynamicMatrix lhs, const DynamicMatrix &rhs)
{
	lhs += rhs;
	return lhs;
}

chcl::DynamicMatrix chcl::operator-(DynamicMatrix lhs, const DynamicMatrix &rhs)
{
	lhs -= rhs;
	return lhs;
}

chcl::DynamicMatrix chcl::operator*(const DynamicMatrix& lhs, const DynamicMatrix &rhs)
{
	if (lhs.getWidth() != rhs.getHeight()) throw std::invalid_argument("Invalid matrices for multiplication.");

	DynamicMatrix result{ rhs.getWidth(), lhs.getHeight() };

	for (unsigned int i = 0; i < lhs.getHeight(); ++i)
	{
		for (unsigned int k = 0; k < lhs.getWidth(); ++k)
		{
			for (unsigned int j = 0; j < rhs.getWidth(); ++j)
			{
				result.at(i, j) += lhs.at(i, k) * rhs.at(k, j);
			}
		}
	}

	return result;
}

void chcl::DynamicMatrix::resize(unsigned int newWidth, unsigned int newHeight)
{
	m_width = newWidth;
	m_height = newHeight;

	m_elements.resize(size_t(newWidth) * newHeight);
}