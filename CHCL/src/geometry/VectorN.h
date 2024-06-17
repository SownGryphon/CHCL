#pragma once

#include <cmath>
#include <ostream>
#include <stdexcept>

#include "maths/Matrix.h"

namespace chcl
{
	template <typename T>
	concept SpecializedVec = requires (T t)
	{
		t.x;
	};

	/**
	 * @brief CRTP Base class for vectors.
	 * @tparam T Type of vector elements.
	 * @tparam dims Vector dimension.
	 */
	template <size_t dims, typename T, template <size_t, typename> typename Derived>
	struct VectorBase
	{
		using ValueType = T;
		using DerivedType = Derived<dims, ValueType>;

		/// Size of vector.
		constexpr size_t size() const { return dims; }

		VectorBase() {}

		template <size_t otherDims, typename T2>
		VectorBase(const Derived<otherDims, T2> &other)
		{
			size_t intersection = std::min(dims, otherDims);
			for (size_t i = 0; i < intersection; ++i)
				this->operator[](i) = other[i];
			for (size_t i = intersection; i < dims; ++i)
				this->operator[](i) = ValueType();
		}

		template <size_t otherDims>
		VectorBase(const Derived<otherDims, ValueType> &other)
		{
			size_t intersection = std::min(dims, otherDims);
			for (size_t i = 0; i < intersection; ++i)
				this->operator[](i) = other[i];
			for (size_t i = intersection; i < dims; ++i)
				this->operator[](i) = ValueType();
		}

		/**
		 * @brief Converts the vector to a column matrix of equal size.
		 * @return Column matrix containing vector elements.
		 */
		Matrix<dims, 1, ValueType> toMatrix() const
		{
			return Matrix<dims, 1, ValueType>(data());
		}

		ValueType* data() requires !SpecializedVec<DerivedType>
		{
			return static_cast<DerivedType*>(this)->position;
		}

		ValueType* data() requires SpecializedVec<DerivedType>
		{
			return &static_cast<DerivedType*>(this)->x;
		}

		const ValueType* data() const requires (!SpecializedVec<DerivedType>)
		{
			return static_cast<const DerivedType*>(this)->position;
		}

		const ValueType* data() const requires SpecializedVec<DerivedType>
		{
			return &static_cast<const DerivedType*>(this)->x;
		}

		/**
		 * @brief Returns vector components inside a std::vector
		 */
		std::vector<ValueType> toStdVector() const
		{
			return std::vector<ValueType>(data(), data() + size());
		}

		/**
		 * @brief Vector dot product.
		 * @param vec1 First vector.
		 * @param vec2 Second vector.
		 * @return Scalar dot product.
		 */
		static ValueType Dot(const DerivedType &vec1, const DerivedType &vec2)
		{
			ValueType total = 0;
			for (size_t i = 0; i < dims; ++i)
			{
				total += vec1[i] * vec2[i];
			}
			return total;
		}

		/**
		 * @brief Finds the angle between two vectors.
		 * 
		 * Uses the cosine representation of the dot product, so only works on types where std::acos is supported.
		 * 
		 * @param vec1 First vector.
		 * @param vec2 Second vector.
		 * @return Radian angle between vectors.
		 */
		static ValueType Angle(const DerivedType &vec1, const DerivedType &vec2)
		{
			return std::acos(Dot(vec1, vec2) / (vec1.mag() * vec2.mag()));
		}

		/**
		 * @brief Gets the n-th dimensional component of the vector.
		 * @param n Desired dimension.
		 * @return Vector with zeroes everywhere, except in the desired dimension, where the value matches the value of the base vector.
		 */
		DerivedType component(size_t n) const
		{
			DerivedType result;
			result[n] = static_cast<const DerivedType*>(this)->operator[](n);
			return result;
		}

		/**
		 * @brief Gets the parallel component of the vector in a given direction.
		 * @param dir Direction to get the parallel component in.
		 * @return Projected vector in the given direction.
		 */
		DerivedType parallelComponent(const DerivedType &dir) const
		{
			return Dot(*static_cast<const DerivedType*>(this), dir) / Dot(dir, dir) * dir;
		}

		/**
		 * @brief Gets the perpendicular component of the vector to the given direction
		 * @param vec Direction to get the perpendicular component to.
		 * @return Perpendicular component to the given direction.
		 */
		DerivedType perpendicularComponent(const DerivedType &vec) const
		{
			return (*static_cast<const DerivedType*>(this)) - parallelComponent(vec);
		}

		/**
		 * @brief Normalize the vector.
		 * @return Normalized vector.
		 */
		DerivedType normalized() const
		{
			return (*static_cast<const DerivedType*>(this)) / mag();
		}

		/**
		 * @brief Set the magnitude of the vector, preserving direction.
		 * @param magnitude Desired vector magnitude.
		 */
		void setMagnitude(ValueType magnitude)
		{
			*static_cast<DerivedType*>(this) *= magnitude / mag();
		}

		/**
		 * @brief Squared magnitude of vector. Use this to avoid a square root.
		 * @return Squared magnitude of vector.
		 */
		ValueType magsq() const
		{
			return Dot(*static_cast<const DerivedType*>(this), *static_cast<const DerivedType*>(this));
		}

		/**
		 * @brief Gets the magnitude of vector.
		 * @return Vector magnitude.
		 */
		ValueType mag() const
		{
			return std::sqrt(magsq());
		}

		const ValueType& operator[](size_t n) const requires !SpecializedVec<DerivedType>
		{
			return static_cast<const DerivedType*>(this)->position[n];
		}

		const ValueType& operator[](size_t n) const requires SpecializedVec<DerivedType>
		{
			return *(&static_cast<const DerivedType*>(this)->x + n);
		}

		ValueType& operator[](size_t n) requires !SpecializedVec<DerivedType>
		{
			return static_cast<DerivedType*>(this)->position[n];
		}

		ValueType& operator[](size_t n) requires SpecializedVec<DerivedType>
		{
			return *(&static_cast<DerivedType*>(this)->x + n);
		}

		explicit operator bool()
		{
			for (size_t i = 0; i < dims; ++i)
			{
				if (static_cast<const DerivedType*>(this)->operator[](i))
					return true;
			}
			return false;
		}

		friend constexpr bool operator!=(const DerivedType &lhs, const DerivedType &rhs)
		{
			return !(lhs == rhs);
		}

		DerivedType operator-()
		{
			DerivedType result;
			for (size_t i = 0; i < dims; ++i)
			{
				result[i] = -static_cast<const DerivedType*>(this)->operator[](i);
			}
			return result;
		}

		DerivedType& operator =(const Matrix<dims, 1, ValueType> &mat)
		{
			if (dims != mat.getRows()) throw std::invalid_argument("Vector matrix initialization requires correct matrix size.");
			for (size_t i = 0; i < dims; ++i)
				static_cast<DerivedType*>(this)->operator[](i) = mat.at(i, 0);
			return *static_cast<DerivedType*>(this);
		}
		
		DerivedType& operator =(const DerivedType &other)
		{
			for (size_t i = 0; i < dims; ++i)
				static_cast<DerivedType*>(this)->operator[](i) = other[i];
			return *static_cast<DerivedType*>(this);
		}
		
		DerivedType& operator =(DerivedType &&other)
		{
			if (static_cast<DerivedType*>(this) != &other)
				for (size_t i = 0; i < dims; ++i)
					std::swap(static_cast<DerivedType*>(this)->operator[](i), other[i]);
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator+=(const DerivedType &other)
		{
			for (size_t i = 0; i < dims; ++i)
				static_cast<DerivedType*>(this)->operator[](i) += other[i];
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator-=(const DerivedType &other)
		{
			for (size_t i = 0; i < dims; ++i)
				static_cast<DerivedType*>(this)->operator[](i) -= other[i];
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator*=(const DerivedType &other)
		{
			for (size_t i = 0; i < dims; ++i)
				static_cast<DerivedType*>(this)->operator[](i) *= other[i];
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator/=(const DerivedType &other)
		{
			for (size_t i = 0; i < dims; ++i)
				static_cast<DerivedType*>(this)->operator[](i) /= other[i];
			return *static_cast<DerivedType*>(this);
		}

		friend DerivedType operator+(const DerivedType &lhs, const DerivedType &rhs)
		{
			DerivedType result{ lhs };
			result += rhs;
			return result;
		}

		friend DerivedType operator-(const DerivedType &lhs, const DerivedType &rhs)
		{
			DerivedType result{ lhs };
			result -= rhs;
			return result;
		}

		friend DerivedType operator*(const DerivedType &lhs, const DerivedType &rhs)
		{
			DerivedType result{ lhs };
			result *= rhs;
			return result;
		}

		friend DerivedType operator/(const DerivedType &lhs, const DerivedType &rhs)
		{
			DerivedType result{ lhs };
			result /= rhs;
			return result;
		}

		operator Matrix<dims, 1, T>() const
		{
			return toMatrix();
		}

		explicit operator std::vector<T>() const
		{
			return toStdVector();
		}

		friend std::ostream& operator<<(std::ostream &stream, const DerivedType &vec)
		{
			stream << '[';
			for (size_t i = 0; i < dims; ++i)
			{
				if (i)
					stream << ", ";
				stream << vec[i];
			}
			stream << ']';
			return stream;
		}
	};

	template <size_t dims = 2, typename T = float>
	struct VectorN : public VectorBase<dims, T, VectorN>
	{
		using BaseType = VectorBase<dims, T, VectorN>;
		using BaseType::VectorBase;
		using BaseType::operator=;
		using ValueType = T;

		ValueType position[dims];

		/**
		 * @brief Default constructor.
		 * 
		 * Default initializes all components.
		 */
		VectorN() : position{} {}

		/**
		 * @brief Scalar construction.
		 * 
		 * Initializes all components to given scalar value.
		 * 
		 * @param scalar Scalar value to initialize all elements to.
		 */
		VectorN(ValueType scalar)
		{
			for (size_t i = 0; i < dims; ++i)
				position[i] = scalar;
		}

		/**
		 * @brief Array constructor.
		 * @param values Array of scalar values to initialize each vector component.
		 */
		VectorN(ValueType values[dims])
		{
			for (size_t i = 0; i < dims; ++i)
				position[i] = values[i];
		}

		VectorN(std::initializer_list <ValueType> values)
		{
			for (size_t i = 0; i < dims; ++i)
				position[i] = *(values.begin() + i);
		}

		VectorN(const Matrix<dims, 1, ValueType> &mat)
		{
			for (size_t i = 0; i < dims; ++i)
				position[i] = mat.at(i, 0);
		}

		VectorN(const VectorN &other)
		{
			for (size_t i = 0; i < dims; ++i)
				position[i] = other[i];
		}

		VectorN(VectorN &&other)
		{
			for (size_t i = 0; i < dims; ++i)
				position[i] = std::move(other[i]);
		}

		friend constexpr bool operator==(const VectorN &lhs, const VectorN &rhs)
		{
			for (size_t i = 0; i < dims; ++i)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}
	};

	template <size_t inDims, size_t outDims, typename T>
	VectorN<outDims, T> operator*(const Matrix<inDims, outDims, T> &mat, const VectorN<inDims, T> &vec)
	{
		return VectorN<outDims, T>(mat * vec.toMatrix());
	}
}