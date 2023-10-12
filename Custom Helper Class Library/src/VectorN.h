#pragma once

#include <stdexcept>
#include <cmath>

#include "Matrix.h"

namespace chcl
{
	template <unsigned int dims = 2>
	struct VectorN
	{
		float position[dims];

		VectorN()
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				position[i] = 0.f;
			}
		}

		VectorN(float val)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				position[i] = val;
			}
		}

		VectorN(float position[dims])
		{
			std::memcpy(this->position, position, sizeof(float) * dims);
		}

		VectorN(std::initializer_list<float> values)
		{
			if (dims != values.size()) throw std::invalid_argument("Vector initializer list must match vector size.");
			std::memcpy(position, values.begin(), sizeof(float) * dims);
		}

		VectorN(const VectorN<dims> &other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				this->position[i] = other.position[i];
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

		static float Dot(const VectorN &vec1, const VectorN& vec2)
		{
			float total = 0;

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

			std::memcpy(result.position, other.position, sizeof(float) * std::min(dims, otherDims));

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
			return Matrix(1, dims, (float*)position);
		}

		float magsq() const
		{
			return Dot(*this, *this);
		}

		inline float mag() const
		{
			return std::sqrtf(magsq());
		}

		inline float operator[](const unsigned int i) const
		{
			return position[i];
		}

		inline float& operator[](const unsigned int i)
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
			std::memcpy(this->position, other.position, sizeof(float) * dims);
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