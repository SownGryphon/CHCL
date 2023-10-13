#pragma once

#include "VectorN.h"

namespace chcl
{
	template <typename T = float>
	struct Vector2 : public VectorN<2, T>
	{
		using VectorN<2, T>::VectorN;

		T &x = VectorN<2, T>::position[0],
			&y = VectorN<2, T>::position[1];

		Vector2()
		{
			x = 0;
			y = 0;
		}

		Vector2(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2(const VectorN<2> &vec) : VectorN<2, T>(vec) {}
		Vector2(const Vector2 &vec)
		{
			this->x = vec.x;
			this->y = vec.y;
		}

		static Vector2 FromAngle(T angle)
		{
			return Vector2(std::cos(angle), std::sin(angle));
		}

		inline Vector2 xComponent() const { return VectorN<2, T>::component(0); }
		inline Vector2 yComponent() const { return VectorN<2, T>::component(1); }

		T arg() const
		{
			return atan2(y, x);
		}
	};
}