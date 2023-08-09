#pragma once

#include <stdexcept>
#include <cmath>

#include "Matrix.h"

#define VecNTemplate template <unsigned int dims>

namespace chcl
{
	VecNTemplate
	struct VectorN;

	VecNTemplate VectorN<dims> operator+(VectorN<dims> lhs, const VectorN<dims>& rhs);
	VecNTemplate VectorN<dims> operator-(VectorN<dims> lhs, const VectorN<dims>& rhs);
	VecNTemplate VectorN<dims> operator*(VectorN<dims> lhs, float val);
	VecNTemplate VectorN<dims> operator/(VectorN<dims> lhs, float val);
	VecNTemplate VectorN<dims> operator*(float val, VectorN<dims> lhs);

	VecNTemplate
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

		VectorN(const VectorN<dims>& other)
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
				result.position[i] = matrix.getValue(0, i);
			}

			return result;
		}

		template <unsigned int otherDims>
		static VectorN Project(const VectorN<otherDims>& other)
		{
			VectorN<dims> result{};

			std::memcpy(result.position, other.position, sizeof(float) * std::min(dims, otherDims));

			return result;
		}

		VectorN component(unsigned int dimension) const
		{
			VectorN result{};

			result.position[dimension] = position[dimension];

			return result;
		}

		VectorN normalised() const
		{
			return *this / mag();
		}

		Matrix toMatrix() const
		{
			Matrix result{ 1, dims, (float*)position };
			return result;
		}

		float magsq() const
		{
			float total = 0;

			for (unsigned int i = 0; i < dims; ++i)
			{
				total += position[i] * position[i];
			}

			return total;
		}

		float mag() const
		{
			return std::sqrtf(magsq());
		}

		float dot(const VectorN& other) const
		{
			float total = 0;

			for (unsigned int i = 0; i < dims; ++i)
			{
				total += position[i] * other.position[i];
			}

			return total;
		}

		VectorN& operator=(const VectorN& other)
		{
			std::memcpy(this->position, other.position, sizeof(float) * dims);
			return *this;
		}

		VectorN& operator+=(const VectorN& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				this->position[i] += other.position[i];
			}

			return *this;
		}

		VectorN& operator-=(const VectorN& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				this->position[i] -= other.position[i];
			}

			return *this;
		}

		VectorN& operator*=(float val)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				position[i] *= val;
			}

			return *this;
		}

		VectorN& operator/=(float val)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				position[i] /= val;
			}

			return *this;
		}
	};

	VecNTemplate VectorN<dims> operator+(VectorN<dims> lhs, const VectorN<dims>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	VecNTemplate VectorN<dims> operator-(VectorN<dims> lhs, const VectorN<dims>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	VecNTemplate VectorN<dims> operator*(VectorN<dims> vec, float val)
	{
		vec *= val;
		return vec;
	}

	VecNTemplate VectorN<dims> operator*(float val, VectorN<dims> vec)
	{
		vec *= val;
		return vec;
	}

	VecNTemplate VectorN<dims> operator/(VectorN<dims> vec, float val)
	{
		vec /= val;
		return vec;
	}
}