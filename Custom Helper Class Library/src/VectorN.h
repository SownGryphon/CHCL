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
			for (unsigned int i = 0; i < dims; ++i)
			{
				position[i] = 0;
			}
		}

		VectorN(T val)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				position[i] = val;
			}
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

		VectorN(const VectorN &other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				this->position[i] = other.position[i];
			}
		}

		template <typename T2>
		VectorN(const VectorN<dims, T2> &vec)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				position[i] = vec.position[i];
			}
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

		template <unsigned int otherDims>
		static VectorN Project(const VectorN<otherDims>& other)
		{
			VectorN<dims> result{};

			std::memcpy(result.position, other.position, sizeof(T) * std::min(dims, otherDims));

			return result;
		}

		inline VectorN component(unsigned int dimension) const
		{
			VectorN result{};

			result.position[dimension] = position[dimension];

			return result;
		}

		inline VectorN normalised() const
		{
			return (*this / mag());
		}

		inline Matrix toMatrix() const
		{
			return Matrix(1, dims, (T*)position);
		}

		T magsq() const
		{
			return Dot(*this, *this);
		}

		inline T mag() const
		{
			return std::sqrtf(magsq());
		}

		inline T operator[](const unsigned int i) const
		{
			return position[i];
		}

		inline T& operator[](const unsigned int i)
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