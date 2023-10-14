#pragma once

#include <stdexcept>
#include <cmath>

#include "Matrix.h"

namespace chcl
{
	template <unsigned int dims = 2, typename T = float>
	struct VectorN
	{
		T position[dims];

		VectorN()
		{
			std::fill(position, position + dims, T(0));
		}

		VectorN(T val)
		{
			std::fill(position, position + dims, val);
		}

		VectorN(T position[dims])
		{
			std::memcpy(this->position, position, sizeof(T) * dims);
		}

		VectorN(std::initializer_list<T> values)
		{
			if (dims != values.size()) throw std::invalid_argument("Vector initializer list must match vector size.");
			std::memcpy(position, values.begin(), sizeof(T) * dims);
		}

		template <unsigned int otherDims, typename T2>
		VectorN(const VectorN<otherDims, T2> &vec)
		{
			for (unsigned int i = 0; i < std::min(dims, otherDims); ++i)
			{
				position[i] = vec.position[i];
			}
		}

		template <unsigned int otherDims>
		VectorN(const VectorN<otherDims, T> &other)
		{
			std::memcpy(position, other.position, sizeof(T) * std::min(dims, otherDims));
		}

		static VectorN FromMatrix(const Matrix& matrix)
		{
			if (matrix.getCols() != 1) throw std::invalid_argument("Matrix must be a column matrix for vector conversion.");
			if (matrix.getRows() != dims) throw std::invalid_argument("Matrix rows must match vector dimensions for vector conversion.");

			VectorN result{};

			for (unsigned int i = 0; i < dims; ++i)
			{
				result.position[i] = matrix.at(0, i);
			}

			return result;
		}

		static T Dot(const VectorN &vec1, const VectorN& vec2)
		{
			T total = 0;

			for (unsigned int i = 0; i < dims; ++i)
			{
				total += vec1.position[i] * vec2.position[i];
			}

			return total;
		}

		VectorN component(unsigned int dimension) const
		{
			VectorN result{};

			result.position[dimension] = position[dimension];

			return result;
		}

		VectorN normalised() const
		{
			return (*this / mag());
		}

		Matrix toMatrix() const
		{
			return Matrix(1, dims, (T*)position);
		}

		T magsq() const
		{
			return Dot(*this, *this);
		}

		T mag() const
		{
			return std::sqrtf(magsq());
		}

		const T& operator[](const unsigned int i) const
		{
			return position[i];
		}

		T& operator[](const unsigned int i)
		{
			return position[i];
		}

		VectorN operator-()
		{
			VectorN result;
			for (unsigned int i = 0; i < dims; ++i)
			{
				result[i] *= -position[i];
			}
			return result;
		}

		VectorN& operator =(const VectorN& other)
		{
			std::memcpy(this->position, other.position, sizeof(T) * dims);
			return *this;
		}

		VectorN& operator+=(const VectorN& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				this->position[i] += other[i];
			}
			return *this;
		}

		VectorN& operator-=(const VectorN& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				this->position[i] -= other[i];
			}
			return *this;
		}

		VectorN& operator*=(const VectorN& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				this->position[i] *= other[i];
			}
			return *this;
		}

		VectorN& operator/=(const VectorN& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				this->position[i] /= other[i];
			}
			return *this;
		}

		explicit operator bool()
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				if (position[i])
					return true;
			}
			return false;
		}

		friend constexpr bool operator==(const VectorN &vec1, const VectorN &vec2) = default;
		friend constexpr bool operator!=(const VectorN &vec1, const VectorN &vec2) = default;

		friend VectorN operator+(const VectorN &lhs, const VectorN &rhs)
		{
			VectorN result = lhs;
			result += rhs;
			return result;
		}

		friend VectorN operator-(const VectorN &lhs, const VectorN &rhs)
		{
			VectorN result = lhs;
			result -= rhs;
			return result;
		}

		friend VectorN operator*(const VectorN &lhs, const VectorN &rhs)
		{
			VectorN result = lhs;
			result *= rhs;
			return result;
		}

		friend VectorN operator/(const VectorN &lhs, const VectorN &rhs)
		{
			VectorN result = lhs;
			result /= rhs;
			return result;
		}
	};
}