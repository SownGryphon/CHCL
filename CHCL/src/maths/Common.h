#pragma once

namespace chcl
{
	template <typename T>
	extern const T PI = T(3.14159265359L);

	template <typename T>
	T toRadians(T degrees)
	{
		return degrees / 180 * PI<T>;
	}

	template <typename T>
	T toDegrees(T degrees)
	{
		return degrees / PI<T> * 180;
	}
}