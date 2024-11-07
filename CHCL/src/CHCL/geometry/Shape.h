#pragma once

#include "chcl/geometry/Vector2.h"

namespace chcl
{
	struct Shape
	{
		virtual bool containsPoint(Vector2<float> point) const = 0;
		virtual Vector2<float> constrainPoint(Vector2<float> point) const = 0;
	};
}