#pragma once

#include <stdexcept>
#include <cmath>

#include "../maths/Matrix.h"

namespace chcl
{
	template <unsigned int dims, typename T, typename Derived>
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
		VectorBase(const VectorBase &other)
		{
			for (unsigned int i = 0; i < std::min(dims, otherDims); ++i)
			{
				(*this)[i] = other[i];
			}
		}

		template <unsigned int otherDims>
		VectorBase(const VectorBase &other)
		{
			std::memcpy(data(), other.data(), std::min(dims, otherDims) * sizeof(T));
		}

		static Derived FromMatrix(const Matrix<1, dims> &matrix)
		{
			if (matrix.getCols() != 1) throw std::invalid_argument("Matrix must be a column matrix for vector conversion.");
			if (matrix.getRows() != dims) throw std::invalid_argument("Matrix rows must match vector dimensions for vector conversion.");

			Derived result;
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

		static T Dot(const Derived &vec1, const Derived& vec2)
		{
			T total = 0;
			for (unsigned int i = 0; i < dims; ++i)
			{
				total += vec1[i] * vec2[i];
			}
			return total;
		}

		static T Angle(const Derived &vec1, const Derived &vec2)
		{
			return std::acos(Dot(vec1, vec2) / (vec1.mag() * vec2.mag()));
		}

		Derived component(unsigned int dimension) const
		{
			Derived result;
			result[dimension] = (*this)[dimension];
			return result;
		}

		Derived normalized()
		{
			return (*static_cast<Derived*>(this)) / mag();
		}

		T magsq() const
		{
			return Dot(*static_cast<const Derived*>(this), *static_cast<const Derived*>(this));
		}

		T mag() const
		{
			return std::sqrt(magsq());
		}

		const T& operator[](unsigned int n) const
		{
			return static_cast<const Derived*>(this)->position[n];
		}

		T& operator[](unsigned int n)
		{
			return static_cast<Derived*>(this)->position[n];
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

		friend constexpr bool operator!=(const Derived &lhs, const Derived &rhs)
		{
			return !(lhs == rhs);
		}

		Derived operator-()
		{
			Derived result;
			for (unsigned int i = 0; i < dims; ++i)
			{
				result[i] *= -(*this)[i];
			}
			return result;
		}

		Derived& operator =(const Matrix<1, dims> &mat)
		{
			if (dims != mat.getRows()) throw std::invalid_argument("Vector matrix initialization requires correct matrix size.");
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] = mat.at(0, i);
			}
			return *static_cast<Derived*>(this);
		}

		Derived& operator+=(const Derived& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] += other[i];
			}
			return *static_cast<Derived*>(this);
		}

		Derived& operator-=(const Derived& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] -= other[i];
			}
			return *static_cast<Derived*>(this);
		}

		Derived& operator*=(const Derived& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] *= other[i];
			}
			return *static_cast<Derived*>(this);
		}

		Derived& operator/=(const Derived& other)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				(*this)[i] /= other[i];
			}
			return *static_cast<Derived*>(this);
		}

		friend Derived operator+(const Derived &lhs, const Derived &rhs)
		{
			Derived result = lhs;
			result += rhs;
			return result;
		}

		friend Derived operator-(const Derived &lhs, const Derived &rhs)
		{
			Derived result = lhs;
			result -= rhs;
			return result;
		}

		friend Derived operator*(const Derived &lhs, const Derived &rhs)
		{
			Derived result = lhs;
			result *= rhs;
			return result;
		}

		friend Derived operator/(const Derived &lhs, const Derived &rhs)
		{
			Derived result = lhs;
			result /= rhs;
			return result;
		}

		operator Matrix<1, dims>()
		{
			return toMatrix();
		}

	protected:
		T* data()
		{
			return static_cast<Derived*>(this)->position;
		}
		const T* data() const
		{
			return static_cast<const Derived*>(this)->position;
		}
	};

	template <unsigned int dims = 2, typename T = float>
	struct VectorN : public VectorBase<dims, T, VectorN<dims, T>>
	{
		using VectorBase<dims, T, VectorN<dims, T>>::VectorBase;
		using VectorBase<dims, T, VectorN<dims, T>>::operator=;

		T position[dims];

		//virtual T& operator[](unsigned int n) override { return position[n]; }
		//virtual const T& operator[](unsigned int n) const override { return position[n]; }

		friend constexpr bool operator==(const VectorN &lhs, const VectorN &rhs)
		{
			for (unsigned int i = 0; i < dims; ++i)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}

		//friend VectorN operator+(const VectorN &lhs, const VectorN &rhs)
		//{
		//	VectorN result = lhs;
		//	result += rhs;
		//	return result;
		//}

		//friend VectorN operator-(const VectorN &lhs, const VectorN &rhs)
		//{
		//	VectorN result = lhs;
		//	result -= rhs;
		//	return result;
		//}

		//friend VectorN operator*(const VectorN &lhs, const VectorN &rhs)
		//{
		//	VectorN result = lhs;
		//	result *= rhs;
		//	return result;
		//}

		//friend VectorN operator/(const VectorN &lhs, const VectorN &rhs)
		//{
		//	VectorN result = lhs;
		//	result /= rhs;
		//	return result;
		//}

	//protected:
	//	virtual T* data() override { return position; }
	//	virtual const T* data() const override { return position; }
	};

	template <unsigned int inDims, unsigned int outDims, typename T>
	VectorN<outDims, T> operator*(const Matrix<inDims, outDims> &mat, const VectorN<inDims, T> &vec)
	{
		VectorN<outDims> result = mat * (vec.toMatrix());
		return result;
	}
}