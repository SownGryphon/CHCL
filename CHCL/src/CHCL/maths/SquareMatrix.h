#pragma once

#include <stdexcept>

#include "chcl/maths/Matrix.h"

namespace chcl
{
	template <size_t size, typename T = float>
	using SquareMatrix = Matrix<size, size, T>;

	template <size_t size, typename T, template<size_t, size_t, typename> typename Derived>
	class SquareMatrixBase : public MatrixBase<size, size, T, Derived>
	{
	public:
		using ValueType = T;
		using BaseType = MatrixBase<size, size, ValueType, Derived>;
		using BaseType::MatrixBase;
		using BaseType::m_values;
		using BaseType::operator =;
		using BaseType::operator+=;
		using BaseType::operator-=;
		using BaseType::operator*=;
		using BaseType::operator/=;
		using DerivedType = Derived<size, size, ValueType>;

		static DerivedType Identity()
		{
			DerivedType result;
			for (size_t i = 0; i < size; ++i)
			{
				result.at(i, i) = ValueType(1);
			}
			return result;
		}

		ValueType determinant() const;
	};

	template <>
	inline float SquareMatrixBase<2, float, Matrix>::determinant() const
	{
		// Using ad - bc
		return m_values[0] * m_values[3] - m_values[1] * m_values[2];
	}

	template <>
	inline float SquareMatrixBase<1, float, Matrix>::determinant() const
	{
		return m_values[0];
	}

	template <size_t size, typename T, template <size_t, size_t, typename> typename Derived>
	T SquareMatrixBase<size, T, Derived>::determinant() const
	{
		T rollingDet = 0.f;						// Adds up the determinants of sum-matrices
		SquareMatrix<size - 1, T> detCalculator;	// Stores each sub-matrix and calculates its determinant

		// Construct a smaller matrix for each element of the current matrix that does not contain the values in that row or column
		for (size_t i = 0; i < size; ++i)
		{
			size_t elementIndex = 0;	// Keeps track of what index of the sub-matrix should be written to
			// Skip first row
			for (size_t j = size; j < size * size; ++j)
			{
				// Skip columns containing the current value
				if (j % size == i % size)
					continue;

				detCalculator.m_values[elementIndex] = m_values[j];

				++elementIndex;
			}

			// Every other sub-determinant needs to be negative
			rollingDet += this->at(i, 0) * detCalculator.determinant() * (i & 1 ? -1.f : 1.f);
		}

		return rollingDet;
	}

	template <size_t size, typename T>
	class Matrix<size, size, T> : public SquareMatrixBase<size, T, Matrix>
	{
	public:
		using SquareMatrixBase<size, T, Matrix>::SquareMatrixBase;
	};
}