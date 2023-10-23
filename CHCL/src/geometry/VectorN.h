#pragma once

#include <stdexcept>
#include <cmath>

#include "maths/Matrix.h"

namespace chcl
{
	template <unsigned int dims, typename T, template <unsigned int, typename> typename Derived>
	struct VectorBase
	{
		VectorBase()
		{
			std::fill(data(), data() + dims, T(0));
		}

		VectorBase(T val)
		{
			std::fill(data(), data() + dims, val);
		}

		VectorBase(T position[dims])
		{
			std::memcpy(data(), position, dims * sizeof(T));
		}

		VectorBase(std::initializer_list<T> values)
		{
			if (dims != values.size()) throw std::invalid_argument("Vector initializer list must match vector size.");
			std::memcpy(data(), values.begin(), dims * sizeof(T));
		}

		explicit VectorBase(const Matrix<1, dims> &mat)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] = mat.at(0, i);
			}
		}

		template <unsigned int otherDims, typename T2>
		VectorBase(const Derived<otherDims, T2> &other)
		{
			for (unsigned int i = 0; i < std::min(dims, otherDims); ++i)
			{
				(*this)[i] = other[i];
			}
		}

		template <unsigned int otherDims>
		VectorBase(const Derived<otherDims, T> &other)
		{
			std::memcpy(data(), other.data(), std::min(dims, otherDims) * sizeof(T));
		}

		static Derived<dims, T> FromMatrix(const Matrix<1, dims> &matrix)
		{
			if (matrix.getCols() != 1) throw std::invalid_argument("Matrix must be a column matrix for vector conversion.");
			if (matrix.getRows() != dims) throw std::invalid_argument("Matrix rows must match vector dimensions for vector conversion.");

			Derived<dims, T> result;
			for (unsigned int i = 0; i < dims; ++i)
			{
				result[i] = matrix.at(0, i);
			}
			return result;
		}

		Matrix<1, dims> toMatrix() const
		{
			return Matrix<1, dims>(data());
		}

		static T Dot(const Derived<dims, T> &vec1, const Derived<dims, T> &vec2)
		{
			T total = 0;
			for (unsigned int i = 0; i < dims; ++i)
			{
				total += vec1[i] * vec2[i];
			}
			return total;
		}

		static T Angle(const Derived<dims, T> &vec1, const Derived<dims, T> &vec2)
		{
			return std::acos(Dot(vec1, vec2) / (vec1.mag() * vec2.mag()));
		}

		Derived<dims, T> component(unsigned int dimension) const
		{
			Derived<dims, T> result;
			result[dimension] = (*this)[dimension];
			return result;
		}

		Derived<dims, T> parallelComponent(const Derived<dims, T> &vec) const
		{
			return Dot(*static_cast<const Derived<dims, T>*>(this), vec) / Dot(vec, vec) * vec;
		}

		Derived<dims, T> perpendicularComponent(const Derived<dims, T> &vec) const
		{
			return (*static_cast<const Derived<dims, T>*>(this)) - parallelComponent(vec);
		}

		Derived<dims, T> normalized() const
		{
			return (*static_cast<const Derived<dims, T>*>(this)) / mag();
		}

		T magsq() const
		{
			return Dot(*static_cast<const Derived<dims, T>*>(this), *static_cast<const Derived<dims, T>*>(this));
		}

		T mag() const
		{
			return std::sqrt(magsq());
		}

		const T& operator[](unsigned int n) const
		{
			return static_cast<const Derived<dims, T>*>(this)->position[n];
		}

		T& operator[](unsigned int n)
		{
			return static_cast<Derived<dims, T>*>(this)->position[n];
		}

		explicit operator bool()
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				if ((*this)[i])
					return true;
			}
			return false;
		}

		friend constexpr bool operator!=(const Derived<dims, T> &lhs, const Derived<dims, T> &rhs)
		{
			return !(lhs == rhs);
		}

		Derived<dims, T> operator-()
		{
			Derived<dims, T> result;
			for (unsigned int i = 0; i < dims; ++i)
			{
				result[i] *= -(*this)[i];
			}
			return result;
		}

		Derived<dims, T>& operator =(const Matrix<1, dims> &mat)
		{
			if (dims != mat.getRows()) throw std::invalid_argument("Vector matrix initialization requires correct matrix size.");
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] = mat.at(0, i);
			}
			return *static_cast<Derived<dims, T>*>(this);
		}

		Derived<dims, T>& operator =(const Derived<dims, T> &other)
		{
			memcpy(data(), other.data(), dims * sizeof(T));
			return *static_cast<Derived<dims, T>*>(this);
		}
		
		Derived<dims, T>& operator+=(const Derived<dims, T> &other)

		Derived<dims, T>& operator-=(const Derived<dims, T> &other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] -= other[i];
			}
			return *static_cast<Derived<dims, T>*>(this);
		}

		Derived<dims, T>& operator*=(const Derived<dims, T> &other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] *= other[i];
			}
			return *static_cast<Derived<dims, T>*>(this);
		}

		Derived<dims, T>& operator/=(const Derived<dims, T> &other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] /= other[i];
			}
			return *static_cast<Derived<dims, T>*>(this);
		}

		friend Derived<dims, T> operator+(const Derived<dims, T> &lhs, const Derived<dims, T> &rhs)
		{
			Derived<dims, T> result = lhs;
			result += rhs;
			return result;
		}

		friend Derived<dims, T> operator-(const Derived<dims, T> &lhs, const Derived<dims, T> &rhs)
		{
			Derived<dims, T> result = lhs;
			result -= rhs;
			return result;
		}

		friend Derived<dims, T> operator*(const Derived<dims, T> &lhs, const Derived<dims, T> &rhs)
		{
			Derived<dims, T> result = lhs;
			result *= rhs;
			return result;
		}

		friend Derived<dims, T> operator/(const Derived<dims, T> &lhs, const Derived<dims, T> &rhs)
		{
			Derived<dims, T> result = lhs;
			result /= rhs;
			return result;
		}

		operator Matrix<1, dims>()
		{
			return toMatrix();
		}

		T* data()
		{
			return static_cast<Derived<dims, T>*>(this)->position;
		}
		const T* data() const
		{
			return static_cast<const Derived<dims, T>*>(this)->position;
		}
	};

	template <unsigned int dims = 2, typename T = float>
	struct VectorN : public VectorBase<dims, T, VectorN>
	{
		using VectorBase<dims, T, VectorN>::VectorBase;
		using VectorBase<dims, T, VectorN>::operator=;

		T position[dims];

		friend constexpr bool operator==(const VectorN &lhs, const VectorN &rhs)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}
	};

	template <unsigned int inDims, unsigned int outDims, typename T>
	VectorN<outDims, T> operator*(const Matrix<inDims, outDims> &mat, const VectorN<inDims, T> &vec)
	{
		VectorN<outDims> result = mat * (vec.toMatrix());
		return result;
	}
}