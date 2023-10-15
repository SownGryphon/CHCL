#include "Matrix.h"

#include <stdexcept>

namespace chcl
{
	Matrix::Matrix()
		: m_cols{ 0 }, m_rows{ 0 }, m_values{ nullptr } {}

	Matrix::Matrix(unsigned int cols, unsigned int rows, float defaultVal)
		: m_cols{ cols }, m_rows{ rows }, m_values{ new float[size_t(cols) * rows] }
	{
		for (unsigned int i = cols * rows; i--;)
		{
			m_values[i] = defaultVal;
		}
	}

	Matrix::Matrix(unsigned int cols, unsigned int rows, const float* values)
		: m_cols{ cols }, m_rows{ rows }, m_values{ new float[size_t(cols) * rows] }
	{
		memcpy(this->m_values, values, size_t(cols) * rows * sizeof(float));
	}

	Matrix::Matrix(unsigned int cols, unsigned int rows, std::initializer_list<float> values)
		: Matrix(cols, rows)
	{
		if (size_t(cols) * rows != values.size())
			throw std::invalid_argument("Initialiser lsit size does not match Matrix size.");

		std::memcpy(m_values, values.begin(), values.size() * sizeof(float));
	}

	Matrix::Matrix(const Matrix &other)
		: Matrix(other.m_cols, other.m_rows, other.m_values)
	{}

	Matrix::~Matrix()
	{
		delete[] m_values;
	}

	Matrix Matrix::Identity(unsigned int size)
	{
		Matrix result(size, size);

		for (unsigned int i = 0; i < size; ++i)
		{
			result.at(i, i) = 1.f;
		}

		return result;
	}

	Matrix Matrix::Rotation2D(float angle)
	{
		return Matrix(2, 2, {
			std::cos(angle), -std::sin(angle),
			std::sin(angle),  std::cos(angle)
		});
	}

	Matrix Matrix::Resize(const Matrix &mat, unsigned int width, unsigned int height)
	{
		Matrix result(width, height);
		for (unsigned int i = 0; i < std::min(mat.m_cols, width); ++i)
		{
			for (unsigned int j = 0; j < std::min(mat.m_rows, height); ++i)
			{
				result.at(i, j) = mat.at(i, j);
			}
		}
		return result;
	}

	const float& Matrix::at(unsigned int col, unsigned int row) const	// Const variant
	{
		if (col >= m_cols)
			throw std::out_of_range("Column out of range.");

		if (row >= m_rows)
			throw std::out_of_range("Row out of range.");

		return m_values[size_t(row) * m_cols + col];

	}

	float& Matrix::at(unsigned int col, unsigned int row)		// Non-const variant
	{
		if (col >= m_cols)
			throw std::out_of_range("Column out of range.");

		if (row >= m_rows)
			throw std::out_of_range("Row out of range.");

		return m_values[size_t(row) * m_cols + col];
	}

	Matrix Matrix::getValueAsMatrix(unsigned int col, unsigned int row) const
	{
		return Matrix(1, 1, at(col, row));
	}

	void Matrix::getCol(unsigned int col, float* out) const
	{
		if (col >= m_rows)
			throw std::out_of_range("Column out of range.");

		for (unsigned int i = 0; i < m_rows; ++i)
		{
			out[i] = at(col, i);
		}
	}

	void Matrix::getRow(unsigned int row, float* out) const
	{
		if (row >= m_rows)
			throw std::out_of_range("Row out of range.");

		for (unsigned int i = 0; i < m_cols; ++i)
		{
			out[i] = at(i, row);
		}
	}

	Matrix Matrix::getColAsMatrix(unsigned int col) const
	{
		float* colValues = new float[m_rows];

		getCol(col, colValues);

		Matrix result{ 1, m_rows, colValues };
		delete[] colValues;

		return result;
	}

	Matrix Matrix::getRowAsMatrix(unsigned int row) const
	{
		float* rowValues = new float[m_cols];

		getCol(row, rowValues);

		Matrix result{ m_cols, 1, rowValues };
		delete[] rowValues;

		return result;
	}

	float Matrix::determinant() const
	{
		if (m_rows != m_cols)
		{
			throw std::logic_error("Attempting to get determinant of non-sqsuare matrix.");
		}

		// Calculate the determinant normally
		if (m_rows == 2)
		{
			// Using ad - bc
			return m_values[0] * m_values[3] - m_values[1] * m_values[2];
		}

		float rollingDet = 0.f;							// Adds up the determinants of sum-matrices
		Matrix detCalculator{ m_rows - 1, m_cols - 1 };	// Stores each sub-matrix and calculates its determinant

		// Construct a smaller matrix for each element of the current matrix that does not contain the values in that row or column
		for (unsigned int i = 0; i < m_cols; ++i)
		{
			unsigned int elementIndex = 0;	// Keeps track of what index of the sub-matrix should be written to
			// Skip first row
			for (unsigned int j = m_cols; j < m_rows * m_cols; ++j)
			{
				// Skip columns containing the current value
				if (j % m_cols == i % m_cols)
					continue;

				detCalculator.m_values[elementIndex] = m_values[j];

				++elementIndex;
			}

			// Every other sub-determinant needs to be negative
			rollingDet += at(i, 0) * detCalculator.determinant() * (i & 1 ? -1.f : 1.f);
		}

		return rollingDet;
	}

	Matrix::operator bool() const
	{
		if (m_cols == 0 && m_rows == 0)
			return false;

		for (unsigned int i = m_cols * m_rows; i--;)
		{
			if (m_values[i] != 0)
			{
				return true;
			}
		}

		return false;
	}

	void Matrix::perValue(std::function<float(float)> func)
	{
		for (unsigned int i = m_rows * m_cols; i--;)
		{
			m_values[i] = func(m_values[i]);
		}
	}

	// Float arithmetic

	Matrix chcl::operator*(const Matrix &matrix, float num)
	{
		Matrix result = matrix;
		result *= num;
		return result;
	}

	Matrix chcl::operator/(const Matrix &matrix, float num)
	{
		Matrix result = matrix;
		result /= num;
		return result;
	}

	Matrix chcl::operator*(float num, const Matrix &matrix)
	{
		Matrix result = matrix;
		result *= num;
		return result;
	}

	// Float assignment

	Matrix& Matrix::operator =(float num)
	{
		std::fill(m_values, m_values + size_t(m_rows) * m_cols, 0.f);
		return *this;
	}

	Matrix& Matrix::operator*=(float num)
	{
		perValue([num](float val) { return val * num; });

		return (*this);
	}

	Matrix& Matrix::operator/=(float num)
	{
		perValue([num](float val) { return val / num; });

		return (*this);
	}

	// Matrix arithmetic

	Matrix chcl::operator+(const Matrix &lhs, const Matrix &rhs)
	{
		Matrix result = lhs;
		result += rhs;
		return result;
	}

	Matrix chcl::operator-(const Matrix &lhs, const Matrix &rhs)
	{
		Matrix result = lhs;
		result -= rhs;
		return result;
	}

	Matrix chcl::operator*(const Matrix &lhs, const Matrix &rhs)
	{
		// Abort if multiplication cannot be done.
		if (lhs.m_cols != rhs.m_rows)
		{
			throw std::invalid_argument("Matrix sizes are not appropriate to execute matrix multiplication.");
		}

		Matrix result{ rhs.m_cols, lhs.m_rows };

		for (unsigned int i = 0; i < lhs.m_rows; ++i)
		{
			for (unsigned int j = 0; j < rhs.m_cols; ++j)
			{
				for (unsigned int k = 0; k < lhs.m_cols; ++k)
				{
					result.at(j, i) += lhs.at(k, i) * rhs.at(j, k);
				}
			}
		}
		return result;
	}

	// Initializer list assignment

	Matrix& Matrix::operator =(std::initializer_list<float> values)
	{
		if (size_t(m_cols) * m_rows != values.size())
			throw(std::invalid_argument("Initializer list size does not match matrix size."));

		std::memcpy(m_values, values.begin(), values.size() * sizeof(float));

		return (*this);
	}

	// Matrix assignment

	Matrix& Matrix::operator =(const Matrix &other)
	{
		// Resize matrix if needed
		if (m_cols != other.m_cols || m_rows != other.m_rows)
		{
			delete[] m_values;

			m_cols = other.m_cols;
			m_rows = other.m_rows;
			m_values = new float[size_t(m_cols) * m_rows];	// Initialises to garbage, but overwritten later anyway.
		}

		memcpy(m_values, other.m_values, size_t(m_cols) * m_rows * sizeof(float));

		return (*this);
	}

	Matrix& Matrix::operator+=(const Matrix &other)
	{
		if (m_rows != other.m_rows || m_cols != other.m_cols)
		{
			throw std::invalid_argument("Matrix sizes do not match.");
		}

		for (unsigned int i = m_rows * m_cols; i--;)
		{
			m_values[i] += other.m_values[i];
		}

		return (*this);
	}

	Matrix& Matrix::operator-=(const Matrix &other)
	{
		if (m_rows != other.m_rows || m_cols != other.m_cols)
		{
			throw std::invalid_argument("Matrix sizes do not match.");
		}

		for (unsigned int i = m_rows * m_cols; i--;)
		{
			m_values[i] -= other.m_values[i];
		}
		return (*this);
	}

	Matrix& Matrix::operator*=(const Matrix &other)
	{
		(*this) = (*this) * other;
		return (*this);
	}

	// Matrix comparison

	bool Matrix::operator==(const Matrix &other) const
	{
		if (m_cols != other.m_cols || m_rows != other.m_rows)
		{
			return false;
		}

		for (unsigned int i = m_cols * m_rows; i--;)
		{
			if (m_values[i] != other.m_values[i])
			{
				return false;
			}
		}

		return true;
	}

	bool Matrix::operator!=(const Matrix &other) const
	{
		return !(*this == other);
	}
}