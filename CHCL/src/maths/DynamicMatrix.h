#pragma once

#include <vector>

#include <maths/Matrix.h>
#include "geometry/Vector2.h"

namespace chcl
{
	/**
	 * @brief Class for dynamically sized matrices.
	 */
	template <typename T>
	class DynamicMatrix
	{
	public:
		using ValueType = T;

		DynamicMatrix() = default;
		DynamicMatrix(size_t rows, size_t cols, ValueType defaultVal = ValueType())
		{
			resize(rows, cols, defaultVal);
		}

		DynamicMatrix(size_t rows, size_t cols, const ValueType *values)
		{
			resize(rows, cols, values);
		}

		DynamicMatrix(size_t rows, size_t cols, const std::vector<ValueType> &values)
		{
			resize(rows, cols, values.data());
		}

		template <size_t rows, size_t cols>
		DynamicMatrix(const Matrix<rows, cols, ValueType> &matrix)
		{
			resize(rows, cols, matrix.values());
		}

		DynamicMatrix(const DynamicMatrix &other)
		{
			resize(other.rows(), other.cols(), other.data());
		}

		DynamicMatrix(DynamicMatrix &&other) :
			m_rows{ other.m_rows }, m_cols{ other.m_cols },
			m_elements{ other.m_elements }
		{
			other.m_rows = 0;
			other.m_cols = 0;
			other.m_elements = nullptr;
		}

		~DynamicMatrix()
		{
			clear();
		}

		inline size_t rows() const { return m_rows; }
		inline size_t cols() const { return m_cols; }
		inline size_t count() const { return m_rows * m_cols; }
		inline Vector2<size_t> size() const { return { m_rows, m_cols }; }

		inline ValueType& at(size_t row, size_t col) { return m_elements[row * m_cols + col]; }
		inline const ValueType& at(size_t row, size_t col) const { return m_elements[row * m_cols + col]; }

		inline ValueType* data() { return m_elements; }
		inline const ValueType* data() const { return m_elements; }
		std::vector<ValueType> dataVector() const
		{
			std::vector<ValueType> result;
			result.assign(data(), data() + count());
			return result;
		}

		DynamicMatrix transpose() const
		{
			DynamicMatrix result{ m_cols, m_rows };

			for (size_t i = 0; i < m_rows; ++i)
				for (size_t j = 0; j < m_cols; ++j)
					result.at(j, i) = at(i, j);

			return result;
		}

		DynamicMatrix& operator =(const DynamicMatrix &other)
		{
			if (size() != other.size()) resize(other.rows(), other.cols(), other.data());
			else
				for (size_t i = count(); i--;)
					m_elements[i] = other.m_elements[i];
			return *this;
		}

		DynamicMatrix& operator =(DynamicMatrix &&other)
		{
			if (this == &other)
				return *this;

			size_t tempRows = m_rows;
			size_t tempCols = m_cols;
			ValueType *tempElements = m_elements;

			m_rows = other.m_rows;
			m_cols = other.m_cols;
			m_elements = other.m_elements;

			other.m_rows = tempRows;
			other.m_cols = tempCols;
			other.m_elements = tempElements;

			return *this;
		}

		DynamicMatrix& operator+=(const DynamicMatrix &other)
		{
			for (size_t i = count(); i--;)
				m_elements[i] += other.m_elements[i];
			return *this;
		}

		DynamicMatrix& operator-=(const DynamicMatrix &other)
		{
			for (size_t i = count(); i--;)
				m_elements[i] -= other.m_elements[i];
			return *this;
		}

		DynamicMatrix& operator*=(const DynamicMatrix &other)
		{
			(*this) = (*this) * other;
			return *this;
		}

		DynamicMatrix& operator*=(ValueType val)
		{
			for (size_t i = count(); i--;)
				m_elements[i] *= val;
			return *this;
		}

		DynamicMatrix& operator/=(ValueType val)
		{
			for (size_t i = count(); i--;)
				m_elements[i] /= val;
			return *this;
		}

		friend DynamicMatrix operator+(DynamicMatrix lhs, const DynamicMatrix &rhs)
		{
			lhs += rhs;
			return lhs;
		}

		friend DynamicMatrix operator-(DynamicMatrix lhs, const DynamicMatrix &rhs)
		{
			lhs -= rhs;
			return lhs;
		}

		friend DynamicMatrix operator*(const DynamicMatrix& lhs, const DynamicMatrix &rhs)
		{
			DynamicMatrix result{ lhs.rows(), rhs.cols() };

			for (unsigned int i = 0; i < lhs.rows(); ++i)
			{
				for (unsigned int k = 0; k < lhs.cols(); ++k)
				{
					for (unsigned int j = 0; j < rhs.cols(); ++j)
					{
						result.at(i, j) += lhs.at(i, k) * rhs.at(k, j);
					}
				}
			}

			return result;
		}

		friend DynamicMatrix operator*(ValueType val, DynamicMatrix mat)
		{
			mat *= val;
			return mat;
		}

		friend DynamicMatrix operator*(DynamicMatrix mat, ValueType val)
		{
			mat *= val;
			return mat;
		}

		friend DynamicMatrix operator/(DynamicMatrix mat, ValueType val)
		{
			mat /= val;
			return mat;
		}

	private:
		size_t m_rows = 0, m_cols = 0;
		ValueType *m_elements = nullptr;

		void clear()
		{
			for (size_t i = m_rows * m_cols; i--;)
				m_elements[i].~ValueType();
			if (m_elements)
				::operator delete(m_elements, count() * sizeof(ValueType));
			m_rows = 0;
			m_cols = 0;
			m_elements = nullptr;
		}

		void resize(size_t newRows, size_t newCols, const ValueType *newValues = nullptr)
		{
			ValueType *newBlock = (ValueType*)::operator new(newRows * newCols * sizeof(ValueType));

			for (size_t i = newRows * newCols; i--;)
				if (newValues)
					new (&newBlock[i]) ValueType(newValues[i]);
				else
					new (&newBlock[i]) ValueType();

			clear();
			m_rows = newRows;
			m_cols = newCols;
			m_elements = newBlock;
		}

		void resize(size_t newRows, size_t newCols, const ValueType newValue)
		{
			ValueType *newBlock = (ValueType*)::operator new(newRows * newCols * sizeof(ValueType));

			for (size_t i = newRows * newCols; i--;)
				new (&newBlock[i]) ValueType(newValue);

			clear();
			m_rows = newRows;
			m_cols = newCols;
			m_elements = newBlock;
		}
	};
}