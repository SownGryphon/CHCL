#pragma once

#include "VectorN.h"
#include "Vector2.h"

namespace chcl
{
	template <typename T = float>
	using Vector3 = VectorN<3, T>;

	template <typename T>
	struct VectorN<3, T> : public VectorBase<3, T, VectorN<3, T>>
	{
		using VectorBase<3, T, VectorN<3, T>>::VectorBase;
		using VectorBase<3, T, VectorN<3, T>>::operator=;

		union
		{
			T position[3];
			struct
			{
				T x, y, z;
			};
			struct
			{
				Vector2<T> xy;
				T z;
			};
			struct
			{
				T x;
				Vector2<T> yz;
			};
		};

		VectorN()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		VectorN(T val)
		{
			x = val;
			y = val;
			z = val;
		}

		VectorN(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		VectorN(const Vector2<T> &xy, T z)
		{
			this->xy = xy;
			this->z = z;
		}

		VectorN(T x, const Vector2<T> &yz)
		{
			this->x = x;
			this->yz = yz;
		}

		template <typename T2>
		VectorN(const VectorN<3, T2> &vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		VectorN(const VectorN<3, T> &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}

		static VectorN Cross(const VectorN &vec1, const VectorN &vec2)
		{
			return VectorN(
				vec1.y * vec2.z - vec1.z * vec2.y,
				vec1.x * vec2.z - vec1.z * vec2.x,
				vec1.x * vec2.y - vec1.y * vec2.x
			);
		}

		VectorN xComponent() const { return VectorN(x, 0, 0); }
		VectorN yComponent() const { return VectorN(0, y, 0); }
		VectorN zComponent() const { return VectorN(0, 0, z); }

		//virtual const T& operator[](unsigned int n) const override { return position[n]; }
		//virtual T& operator[](unsigned int n) override { return position[n]; }

		explicit operator bool()
		{
			return x && y && z;
		}

		VectorN& operator =(T val)
		{
			x = val;
			y = val;
			z = val;
			return *this;
		}

		VectorN& operator =(const VectorN &other)
		{
			std::memcpy(position, other.position, 3 * sizeof(T));
			return *this;
		}

		VectorN& operator+=(const VectorN &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		VectorN& operator-=(const VectorN &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		VectorN& operator*=(const VectorN &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		VectorN& operator/=(const VectorN &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		friend VectorN operator+(const VectorN &lhs, const VectorN &rhs)
		{
			VectorN result = lhs;
			result += rhs;
			return result;
		}

		friend VectorN operator-(const VectorN &lhs, const VectorN &rhs)
		{
			VectorN result = lhs;
			result -= rhs;
			return result;
		}

		friend VectorN operator*(const VectorN &lhs, const VectorN &rhs)
		{
			VectorN result = lhs;
			result *= rhs;
			return result;
		}

		friend VectorN operator/(const VectorN &lhs, const VectorN &rhs)
		{
			VectorN result = lhs;
			result /= rhs;
			return result;
		}

	//protected:
	//	virtual T* data() override { return position; }
	//	virtual const T* data() const override { return position; }
	};
}