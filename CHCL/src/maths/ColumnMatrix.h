#pragma once

#include "Matrix.h"
#include "SquareMatrix.h"

namespace chcl
{
	template <unsigned int size>
	class ColumnMatrix : public MatrixBase<1, size, Matrix>
	{
	public:
		ColumnMatrix(float val = 0.f)
			: MatrixBase(1, size, val)
		{}

		ColumnMatrix(const ColumnMatrix &other)
			: MatrixBase(other.m_cols, other.m_rows)
		{
			std::memcpy(m_values, other.m_values, size * sizeof(float));
		}

		ColumnMatrix& operator =(const ColumnMatrix &other)
		{
			std::memcpy(m_values, other.m_values, size * sizeof(float));
		}

		ColumnMatrix& operator+=(const ColumnMatrix &other)
		{
			for (unsigned int i = 0; i < size; ++i)
			{
				m_values[i] += other.m_values[i];
			}
		}

		ColumnMatrix& operator-=(const ColumnMatrix &other)
		{
			for (unsigned int i = 0; i < size; ++i)
			{
				m_values[i] -= other.m_values[i];
			}
		}



		friend ColumnMatrix operator*(const SquareMatrix<size> &lhs, const ColumnMatrix &rhs);
	};
}