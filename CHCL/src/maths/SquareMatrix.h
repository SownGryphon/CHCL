#pragma once

#include "Matrix.h"

#include <stdexcept>

namespace chcl
{
	template <unsigned int size>
	class SquareMatrix : public Matrix
	{
	public:
		SquareMatrix() : Matrix(size, size) {}
		SquareMatrix(float val) : Matrix(size, size, val) {}
		SquareMatrix(const float *vals) : Matrix(size, size, vals) {}
		template <unsigned int otherSize>
		SquareMatrix(const SquareMatrix<otherSize> &other) : Matrix(Matrix::Resize(other, size, size)) {}
		SquareMatrix(const SquareMatrix &other) : Matrix(other) {}
		SquareMatrix(const Matrix &other) : Matrix(Matrix::Resize(other, size, size)) {}

		SquareMatrix(std::initializer_list<float> values)
			: Matrix(size, size)
		{
			if (size_t(size) * size != values.size())
				throw std::invalid_argument("Initialiser lsit size does not match Matrix size.");

			std::memcpy(m_values, values.begin(), values.size() * sizeof(float));
		}

		static SquareMatrix Identity()
		{
			Matrix result(size, size);
			for (unsigned int i = 0; i < size; ++i)
			{
				result.at(i, i) = 1.f;
			}
			return result;
		}

		operator Matrix()
		{
			return *this;
		}
	};

	class Mat2 : public SquareMatrix<2>
	{
	public:
		using SquareMatrix<2>::SquareMatrix;

		static Mat2 Rotation(float angle);
	};

	class Mat4 : public SquareMatrix<4>
	{
	public:
		using SquareMatrix<4>::SquareMatrix;

		static Mat4 Ortho(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		static Mat4 Translation(float x, float y, float z);
		static Mat4 Scale(float x, float y, float z);
		static Mat4 Rotation2D(float radians);
	};
}