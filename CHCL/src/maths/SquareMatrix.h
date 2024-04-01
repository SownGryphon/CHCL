#pragma once

#include "Matrix.h"

#include <stdexcept>

namespace chcl
{
	template <unsigned int size, typename T = float>
	using SquareMatrix = Matrix<size, size, T>;

	template <unsigned int size, typename T, template<unsigned int, unsigned int, typename> typename Derived>
	class SquareMatrixBase : public MatrixBase<size, size, T, Derived>
	{
	public:
		using MatrixBase<size, size, T, Derived>::MatrixBase;
		using MatrixBase<size, size, T, Derived>::m_values;
		using MatrixBase<size, size, T, Derived>::operator =;
		using MatrixBase<size, size, T, Derived>::operator+=;
		using MatrixBase<size, size, T, Derived>::operator-=;
		using MatrixBase<size, size, T, Derived>::operator*=;
		using MatrixBase<size, size, T, Derived>::operator/=;

		static Derived<size, size, T> Identity()
		{
			Derived<size, size, T> result;
			for (unsigned int i = 0; i < size; ++i)
			{
				result.at(i, i) = 1.f;
			}
			return result;
		}

		T determinant() const;
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

	template <unsigned int size, typename T, template <unsigned int, unsigned int, typename> typename Derived>
	T SquareMatrixBase<size, T, Derived>::determinant() const
	{
		T rollingDet = 0.f;						// Adds up the determinants of sum-matrices
		SquareMatrix<size - 1, T> detCalculator;	// Stores each sub-matrix and calculates its determinant

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

	template <unsigned int size, typename T>
	class Matrix<size, size, T> : public SquareMatrixBase<size, T, Matrix>
	{
	public:
		using SquareMatrixBase<size, T, Matrix>::SquareMatrixBase;
	};

	using Mat2 = SquareMatrix<2, float>;
	template <>
	class Matrix<2, 2, float> : public SquareMatrixBase<2, float, Matrix>
	{
	public:
		using SquareMatrixBase<2, float, Matrix>::SquareMatrixBase;

		static Mat2 Rotation(float angle);
	};

	using Mat3 = SquareMatrix<3, float>;
	template <>
	class Matrix<3, 3, float> : public SquareMatrixBase<3, float, Matrix>
	{
	public:
		using SquareMatrixBase<3, float, Matrix>::SquareMatrixBase;

		static Mat3 Rotation(float pitch, float yaw);
	};

	using Mat4 = SquareMatrix<4, float>;
	template <>
	class Matrix<4, 4, float> : public SquareMatrixBase<4, float, Matrix>
	{
	public:
		using SquareMatrixBase<4, float, Matrix>::SquareMatrixBase;

		static Mat4 Ortho(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		static Mat4 Translation(float x, float y, float z);
		static Mat4 Scale(float x, float y, float z);
		static Mat4 Rotation2D(float radians);
	};
}