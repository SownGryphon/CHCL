#pragma once

#include "Matrix.h"

#include <stdexcept>

namespace chcl
{
	template <unsigned int size>
	using SquareMatrix = Matrix<size, size>;

	template <unsigned int size, template<unsigned int, unsigned int> typename Derived>
	class SquareMatrixBase : public MatrixBase<size, size, Derived>
	{
	public:
		using MatrixBase<size, size, Derived>::MatrixBase;
		using MatrixBase<size, size, Derived>::m_values;
		using MatrixBase<size, size, Derived>::operator =;
		using MatrixBase<size, size, Derived>::operator+=;
		using MatrixBase<size, size, Derived>::operator-=;
		using MatrixBase<size, size, Derived>::operator*=;
		using MatrixBase<size, size, Derived>::operator/=;

		SquareMatrixBase(const MatrixBase<size, size, Derived> &mat) : MatrixBase<size, size, Derived>::MatrixBase(mat) {}

		static Derived<size, size> Identity()
		{
			Derived<size, size> result;
			for (unsigned int i = 0; i < size; ++i)
			{
				result.at(i, i) = 1.f;
			}
			return result;
		}

		float determinant() const;
	};

	template <>
	inline float SquareMatrixBase<2, Matrix>::determinant() const
	{
		// Using ad - bc
		return m_values[0] * m_values[3] - m_values[1] * m_values[2];
	}

	template <>
	inline float SquareMatrixBase<1, Matrix>::determinant() const
	{
		return m_values[0];
	}

	template <unsigned int size, template <unsigned int, unsigned int> typename Derived>
	float SquareMatrixBase<size, Derived>::determinant() const
	{
		float rollingDet = 0.f;						// Adds up the determinants of sum-matrices
		SquareMatrix<size - 1> detCalculator;	// Stores each sub-matrix and calculates its determinant

		// Construct a smaller matrix for each element of the current matrix that does not contain the values in that row or column
		for (unsigned int i = 0; i < size; ++i)
		{
			unsigned int elementIndex = 0;	// Keeps track of what index of the sub-matrix should be written to
			// Skip first row
			for (unsigned int j = size; j < size * size; ++j)
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

	template <unsigned int size>
	class Matrix<size, size> : public SquareMatrixBase<size, Matrix>
	{
	public:
		using SquareMatrixBase<size, Matrix>::SquareMatrixBase;
	};

	using Mat2 = SquareMatrix<2>;

	template <>
	class Matrix<2, 2> : public SquareMatrixBase<2, Matrix>
	{
	public:
		using SquareMatrixBase<2, Matrix>::SquareMatrixBase;

		Matrix(const SquareMatrix<2> &mat) : SquareMatrixBase<2, Matrix>(mat) {}

		static Mat2 Rotation(float angle);
	};

	using Mat4 = SquareMatrix<4>;

	template <>
	class Matrix<4, 4> : public SquareMatrixBase<4, Matrix>
	{
	public:
		using SquareMatrixBase<4, Matrix>::SquareMatrixBase;

		Matrix(const SquareMatrixBase<4, Matrix> &mat) : SquareMatrixBase<4, Matrix>(mat) {}

		static Mat4 Ortho(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		static Mat4 Translation(float x, float y, float z);
		static Mat4 Scale(float x, float y, float z);
		static Mat4 Rotation2D(float radians);
	};
}