#pragma once

#include "Matrix.h"

#include <stdexcept>

namespace chcl
{
	template <unsigned int size>
	using SquareMatrix = Matrix<size, size>;

	template <unsigned int size>
	class Matrix<size, size> : public MatrixBase<size, size>
	{
	public:
		using MatrixBase<size, size>::MatrixBase;
		using MatrixBase<size, size>::m_values;

		Matrix(const MatrixBase<size, size> &mat) : MatrixBase<size, size>::MatrixBase(mat) {}

		static Matrix Identity()
		{
			Matrix result;
			for (unsigned int i = 0; i < size; ++i)
			{
				result.at(i, i) = 1.f;
			}
			return result;
		}

		float determinant() const;
	};

	template <>
	inline float SquareMatrix<2>::determinant() const
	{
		// Using ad - bc
		return m_values[0] * m_values[3] - m_values[1] * m_values[2];
	}

	template <>
	inline float SquareMatrix<1>::determinant() const
	{
		return m_values[0];
	}

	template <unsigned int size>
	float SquareMatrix<size>::determinant() const
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

	class Mat2 : public SquareMatrix<2>
	{
	public:
		using SquareMatrix<2>::SquareMatrix;

		Mat2(const SquareMatrix<2> &mat) : SquareMatrix<2>(mat) {}

		static Mat2 Rotation(float angle);
	};

	class Mat4 : public SquareMatrix<4>
	{
	public:
		using SquareMatrix<4>::SquareMatrix;

		Mat4(const SquareMatrix<4> &mat) : SquareMatrix<4>(mat) {}

		static Mat4 Ortho(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		static Mat4 Translation(float x, float y, float z);
		static Mat4 Scale(float x, float y, float z);
		static Mat4 Rotation2D(float radians);
	};
}