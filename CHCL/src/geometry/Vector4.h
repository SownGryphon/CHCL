#pragma once

#include "VectorN.h"
#include "Vector2.h"

namespace chcl
{
	template <typename T = float>
	using Vector4 = VectorN<4, T>;

	template <typename T>
	struct VectorN<4, T> : public VectorBase<4, T, VectorN<4, T>>
	{
		using VectorBase<4, T, VectorN<4, T>>::VectorBase;
		using VectorBase<4, T, VectorN<4, T>>::operator=;

		union
		{
			T position[4];
			struct
			{
				float x, y, z, w;
			};
			struct
			{
				Vector2<T> xy, zw;
			};
		};

		VectorN()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		VectorN(T val)
		{
			x = val;
			y = val;
			z = val;
			w = val;
		}

		VectorN(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		template <typename T2>
		VectorN(const VectorN<4, T2> &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

		VectorN(const VectorN<4, T> &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;
		}

		VectorN xComponent() const { return VectorN(x, 0, 0, 0); }
		VectorN yComponent() const { return VectorN(0, y, 0, 0); }
		VectorN zComponent() const { return VectorN(0, 0, z, 0); }
		VectorN wComponent() const { return VectorN(0, 0, 0, w); }

		explicit operator bool()
		{
			return x && y && z && w;
		}

		VectorN& operator =(T val)
		{
			x = val;
			y = val;
			z = val;
			w = val;
			return *this;
		}

		VectorN& operator =(const VectorN &other)
		{
			std::memcpy(position, other.position, 4 * sizeof(T));
			return *this;
		}

		VectorN& operator+=(const VectorN &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		VectorN& operator-=(const VectorN &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		VectorN& operator*=(const VectorN &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			z *= other.w;
			return *this;
		}

		VectorN& operator/=(const VectorN &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			z /= other.w;
			return *this;
		}
	};
}