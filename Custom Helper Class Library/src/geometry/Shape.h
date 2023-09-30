#pragma once

#include "../Vector2.h"

namespace chcl
{
	struct Shape
	{
		virtual bool containsPoint(const Vector2 &vec) const = 0;
		virtual Vector2 constrainPoint(Vector2 vec) const = 0;
	};
}