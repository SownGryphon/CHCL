#pragma once

#include "geometry/VectorN.h"
#include "geometry/Vector2.h"

namespace chcl
{
	template <typename T = float>
	using Vector4 = VectorN<4, T>;

	template <typename T>
	struct VectorN<4, T> : public VectorBase<4, T, VectorN>
	{
		VECTORN_CLASS(4, T);

		ValueType x, y, z, w;

		VectorN() : x{}, y{}, z{}, w{} {}

		VectorN(ValueType val) :
			x{ val }, y{ val }, z{ val }, w{ val }
		{}

		VectorN(ValueType x, ValueType y, ValueType z, ValueType w) :
			x{ x }, y{ y }, z{ z }, w{ w }
		{}

		VectorN(const Matrix<4, 1, ValueType> &mat) :
			x{ mat.at(0, 0) }, y{ mat.at(1, 0) }, z{ mat.at(2, 0) }, w{ mat.at(3, 0) }
		{}

		template <typename T2>
		VectorN(const VectorN<4, T2> &other) :
			x{ other.x }, y{ other.y }, z{ other.z }, w{ other.w }
		{}

		DerivedType xComponent() const { return DerivedType(x, 0, 0, 0); }
		DerivedType yComponent() const { return DerivedType(0, y, 0, 0); }
		DerivedType zComponent() const { return DerivedType(0, 0, z, 0); }
		DerivedType wComponent() const { return DerivedType(0, 0, 0, w); }

		explicit operator bool()
		{
			return x || y || z || w;
		}

		friend bool operator==(const DerivedType &lhs, const DerivedType &rhs)
		{
			return lhs.x == rhs.x
				&& lhs.y == rhs.y
				&& lhs.z == rhs.z
				&& lhs.w == rhs.w;
		}

		VectorN& operator =(ValueType val)
		{
			x = val;
			y = val;
			z = val;
			w = val;
			return *this;
		}

		VectorN& operator+=(const DerivedType &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		VectorN& operator-=(const DerivedType &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		VectorN& operator*=(const DerivedType &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			z *= other.w;
			return *this;
		}

		VectorN& operator/=(const DerivedType &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			z /= other.w;
			return *this;
		}
	};
}