#pragma once

#include "Shape.h"
#include "Circle.h"
#include "AlignedRect.h"

namespace chcl
{
	template <typename T>
	concept ShapeDerived = std::is_base_of<Shape, T>::value;

	template <ShapeDerived T1, ShapeDerived T2>
	bool checkOverlap(const T1 &shape1, const T2 &shape2)
	{
		static bool called = false;

		if (called)
			return false;

		called = true;
		bool result = checkOverlap(shape2, shape1);
		called = false;
		return result;
	}

	template <>
	bool checkOverlap(const Circle &c1, const Circle &c2);
	template <>
	bool checkOverlap(const Circle &circle, const AlignedRect &rect);
	template <>
	bool checkOverlap(const AlignedRect &r1, const AlignedRect &r2);
}