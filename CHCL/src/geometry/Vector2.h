#pragma once

#include "VectorN.h"

namespace chcl
{
	template <typename T = float>
	using Vector2 = VectorN<2, T>;

	template <typename T>
	struct VectorN<2, T> : public VectorBase<2, T, VectorN>
	{
		using VectorBase<2, T, VectorN>::VectorBase;
		using VectorBase<2, T, VectorN>::operator=;

		union
		{
			T position[2];
			struct
			{
				T x, y;
			};
		};

		VectorN()
		{
			x = 0;
			y = 0;
		}

		VectorN(T val)
		{
			x = val;
			y = val;
		}

		VectorN(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		VectorN(const Matrix<2, 1> &mat)
		{
			x = mat.at(0, 0);
			y = mat.at(1, 0);
		}

		template <typename T2>
		VectorN(const VectorN<2, T2> &other)
		{
			x = other.x;
			y = other.y;
		}

		VectorN(const VectorN<2, T> &other)
		{
			x = other.x;
			y = other.y;
		}

		static VectorN<2, T> FromAngle(T angle)
		{
			return VectorN<2, T>(std::cos(angle), std::sin(angle));
		}

		VectorN xComponent() const { return VectorN(x, 0); }
		VectorN yComponent() const { return VectorN(0, y); }

		T arg() const
		{
			return atan2(y, x);
		}

		//virtual const T& operator[](unsigned int n) const override { return position[n]; }
		//virtual T& operator[](unsigned int n) override { return position[n]; }

		explicit operator bool()
		{
			return x && y;
		}

		friend bool operator==(const VectorN &vec1, const VectorN &vec2)
		{
			return vec1.x == vec2.x
				&& vec1.y == vec2.y;
		}

		VectorN& operator =(T val)
		{
			x = val;
			y = val;
			return *this;
		}

		VectorN& operator =(const Matrix<2, 1> &mat)
		{
			x = mat.at(0, 0);
			y = mat.at(1, 0);
			return *this;
		}

		VectorN& operator+=(const VectorN &other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		VectorN& operator-=(const VectorN &other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		VectorN& operator*=(const VectorN &other)
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		VectorN& operator/=(const VectorN &other)
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}

		//friend VectorN operator+(const VectorN &lhs, const VectorN &rhs)
		//{
		//	Vector2 result = lhs;
		//	result += rhs;
		//	return result;
		//}

		//friend VectorN operator-(const VectorN &lhs, const VectorN &rhs)
		//{
		//	Vector2 result = lhs;
		//	result -= rhs;
		//	return result;
		//}

		//friend VectorN operator*(const VectorN &lhs, const VectorN &rhs)
		//{
		//	Vector2 result = lhs;
		//	result *= rhs;
		//	return result;
		//}

		//friend VectorN operator/(const VectorN &lhs, const VectorN &rhs)
		//{
		//	Vector2 result = lhs;
		//	result /= rhs;
		//	return result;
		//}

	//protected:
	//	virtual T* data() override { return position; }
	//	virtual const T* data() const override { return position; }
	};
}