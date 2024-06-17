#include "Rect.h"

namespace chcl
{
	bool Rect::containsPoint(chcl::Vector2<float> point) const
	{
		return true;
	}

	Vector2<float> Rect::constrainPoint(Vector2<float> point) const
	{
		return point;
	}
}