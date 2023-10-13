#pragma once

#include "VectorN.h"

namespace chcl
{
	template <typename T = float>
	struct Vector3 : public VectorN<3, T>
	{
		using VectorN<3, T>::VectorN;

		T &x = VectorN<3, T>::position[0],
			&y = VectorN<3, T>::position[1],
			&z = VectorN<3, T>::position[2];

		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3(const VectorN<3>& vec)
		{
			x = vec.position[0];
			y = vec.position[1];
			z = vec.position[2];
		}

		Vector3(const Vector3 &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		static Vector3 Cross(const Vector3 &vec1, const Vector3 &vec2)
		{
			return Vector3(
				vec1.y * vec2.z - vec1.z * vec2.y,
				vec1.x * vec2.z - vec1.z * vec2.x,
				vec1.x * vec2.y - vec1.y * vec2.x
			);
		}

		inline Vector3 xComponent() const { return VectorN<3, T>::component(0); }
		inline Vector3 yComponent() const { return VectorN<3, T>::component(1); }
		inline Vector3 zComponent() const { return VectorN<3, T>::component(2); }
	};
}