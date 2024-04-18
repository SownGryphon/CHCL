#include "DynamicMatrix.h"

#include <stdexcept>

chcl::DynamicMatrix::DynamicMatrix() :
	m_cols(0), m_rows(0)
{}

chcl::DynamicMatrix::DynamicMatrix(unsigned int rows, unsigned int cols, float defaultVal) :
	m_rows(rows), m_cols(cols)
{
	m_elements.resize(size_t(rows) * cols, defaultVal);
}

chcl::DynamicMatrix::DynamicMatrix(unsigned int rows, unsigned int cols, const std::vector<float> &values)
{
	if (values.size() != size_t(rows) * cols) throw std::invalid_argument("Invalid vector size for intializing matrix.");

	m_rows = rows;
	m_cols = cols;
	m_elements = values;
}

chcl::DynamicMatrix::DynamicMatrix(const DynamicMatrix &other) :
	m_cols(other.m_cols), m_rows(other.m_rows),
	m_elements(other.m_elements)
{}

chcl::DynamicMatrix::DynamicMatrix(DynamicMatrix &&other) :
	m_cols(other.m_cols), m_rows(other.m_rows)
{
	m_elements = std::move(other.m_elements);
	other.m_cols = 0;
	other.m_rows = 0;
}

float& chcl::DynamicMatrix::at(unsigned int row, unsigned int col)
{
	if (row > m_rows || col > m_cols) throw std::out_of_range("Matrix access location out of range.");

	return m_elements[size_t(row) * m_cols + col];
}

const float& chcl::DynamicMatrix::at(unsigned int row, unsigned int col) const
{
	if (row > m_rows || col > m_cols) throw std::out_of_range("Matrix access location out of range.");

	return m_elements[size_t(row) * m_cols + col];
}

chcl::DynamicMatrix chcl::DynamicMatrix::transpose() const
{
	DynamicMatrix result(m_cols, m_rows);

	for (unsigned int i = 0; i < m_rows; ++i)
		for (unsigned int j = 0; j < m_cols; ++j)
			result.at(j, i) = at(i, j);

	return result;
}

chcl::DynamicMatrix& chcl::DynamicMatrix::operator=(const DynamicMatrix &other)
{
	if (other.size() != size()) resize(other.size());

	for (unsigned int i = 0; i < m_rows; ++i)
	{
		for (unsigned int j = 0; j < m_cols; ++j)
		{
			at(i, j) = other.at(i, j);
		}
	}

	return *this;
}

chcl::DynamicMatrix& chcl::DynamicMatrix::operator+=(const DynamicMatrix &other)
{
	if (other.size() != size()) throw std::invalid_argument("Matrix sizes do not match for addition.");

	for (unsigned int i = 0; i < m_rows; ++i)
	{
		for (unsigned int j = 0; j < m_cols; ++j)
		{
			at(i, j) += other.at(i, j);
		}
	}

	return *this;
}

chcl::DynamicMatrix& chcl::DynamicMatrix::operator-=(const DynamicMatrix &other)
{
	if (other.size() != size()) throw std::invalid_argument("Matrix sizes do not match for subtraction.");

	for (unsigned int i = 0; i < m_rows; ++i)
	{
		for (unsigned int j = 0; j < m_cols; ++j)
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
	if (lhs.rows() != rhs.cols()) throw std::invalid_argument("Invalid matrices for multiplication.");

	DynamicMatrix result{ rhs.rows(), lhs.cols() };

	for (unsigned int i = 0; i < lhs.cols(); ++i)
	{
		for (unsigned int k = 0; k < lhs.rows(); ++k)
		{
			for (unsigned int j = 0; j < rhs.rows(); ++j)
			{
				result.at(i, j) += lhs.at(i, k) * rhs.at(k, j);
			}
		}
	}

	return result;
}

void chcl::DynamicMatrix::resize(unsigned int newWidth, unsigned int newHeight)
{
	m_cols = newWidth;
	m_rows = newHeight;

	m_elements.resize(size_t(newWidth) * newHeight);
}