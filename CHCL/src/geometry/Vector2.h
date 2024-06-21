#pragma once

#include "VectorN.h"

namespace chcl
{
	template <typename T = float>
	using Vector2 = VectorN<2, T>;

	template <typename T>
	struct VectorN<2, T> : public VectorBase<2, T, VectorN>
	{
		VECTORN_CLASS(2, T);

		ValueType x, y;

		VectorN() : x{}, y{} {}

		VectorN(ValueType val) :
			x{ val }, y{ val }
		{}

		VectorN(ValueType x, ValueType y) :
			x{ x }, y{ y }
		{}

		VectorN(const Matrix<2, 1, ValueType> &mat) :
			x{ mat.at(0, 0) }, y{ mat.at(1, 0) }
		{}

		template <typename T2>
		VectorN(const VectorN<2, T2> &other) :
			x{ other.x }, y{ other.y }
		{}

		/**
		 * @brief Constructs a unit Vector2 from an angle.
		 * @param angle Radian angle of vector.
		 * @return Unit Vector2 pointing in desired direction.
		 */
		static DerivedType FromAngle(ValueType angle)
		{
			return DerivedType(std::cos(angle), std::sin(angle));
		}

		DerivedType xComponent() const { return DerivedType(x, 0); }
		DerivedType yComponent() const { return DerivedType(0, y); }

		/**
		 * @brief Angle of vector.
		 * @return Radian angle.
		 */
		ValueType arg() const
		{
			return atan2(y, x);
		}

		explicit operator bool()
		{
			return x || y;
		}

		friend bool operator==(const DerivedType &vec1, const DerivedType &vec2)
		{
			return vec1.x == vec2.x
				&& vec1.y == vec2.y;
		}

		VectorN& operator =(ValueType val)
		{
			x = val;
			y = val;
			return *this;
		}

		VectorN& operator =(const Matrix<2, 1, ValueType> &mat)
		{
			x = mat.at(0, 0);
			y = mat.at(1, 0);
			return *this;
		}

		VectorN& operator+=(const DerivedType &other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		
		VectorN& operator-=(const DerivedType &other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		VectorN& operator*=(const DerivedType &other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		VectorN& operator/=(const DerivedType &other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}
	};
}