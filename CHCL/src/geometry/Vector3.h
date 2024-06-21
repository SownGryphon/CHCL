#pragma once

#include "VectorN.h"
#include "Vector2.h"

namespace chcl
{
	template <typename T = float>
	using Vector3 = VectorN<3, T>;

	template <typename T>
	struct VectorN<3, T> : public VectorBase<3, T, VectorN>
	{
		VECTORN_CLASS(3, T);

		ValueType x, y, z;

		VectorN() : x{}, y{}, z{} {}

		VectorN(ValueType val) :
			x{ val }, y{ val }, z{ val }
		{}

		VectorN(ValueType x, ValueType y, ValueType z) :
			x{ x }, y{ y }, z{ z }
		{}

		VectorN(const Matrix<3, 1, ValueType> &mat) :
			x{ mat.at(0, 0) }, y{ mat.at(1, 0) }, z{ mat.at(2, 0) }
		{}

		template <typename T2>
		VectorN(const VectorN<3, T2> &other) :
			x{ other.x }, y{ other.y }, z{ other.z }
		{}

		/**
		 * @brief 3D Vector cross product
		 * @param vec1 First vector
		 * @param vec2 Second vector
		 * @return Cross product of vectors
		 */
		static DerivedType Cross(const DerivedType &vec1, const DerivedType &vec2)
		{
			return DerivedType(
				vec1.y * vec2.z - vec1.z * vec2.y,
				vec1.x * vec2.z - vec1.z * vec2.x,
				vec1.x * vec2.y - vec1.y * vec2.x
			);
		}

		DerivedType xComponent() const { return DerivedType(x, 0, 0); }
		DerivedType yComponent() const { return DerivedType(0, y, 0); }
		DerivedType zComponent() const { return DerivedType(0, 0, z); }

		explicit operator bool()
		{
			return x || y || z;
		}

		friend bool operator==(const DerivedType &lhs, const DerivedType &rhs)
		{
			return lhs.x == rhs.x
				&& lhs.y == rhs.y
				&& lhs.z == rhs.z;
		}

		VectorN& operator =(ValueType val)
		{
			x = val;
			y = val;
			z = val;
			return *this;
		}

		VectorN& operator+=(const DerivedType &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		VectorN& operator-=(const DerivedType &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		VectorN& operator*=(const DerivedType &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		VectorN& operator/=(const DerivedType &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}
	};
}