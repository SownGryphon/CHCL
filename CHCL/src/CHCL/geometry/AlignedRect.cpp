#include "AlignedRect.h"

using namespace chcl;

AlignedRect::AlignedRect(float x, float y, float width, float height)
	: origin(x, y), size(width, height) {}

AlignedRect::AlignedRect(const Vector2<float> &origin, const Vector2<float> &size)
	: origin(origin), size(size) {}

bool AlignedRect::containsPoint(Vector2<float> vec) const
{
	return vec.x >= origin.x && vec.x <= origin.x + size.x
		&& vec.y >= origin.y && vec.y <= origin.y + size.y;
}

Vector2<> AlignedRect::constrainPoint(Vector2<float> vec) const
{
	if (vec.x < origin.x) vec.x = origin.x;
	else if (vec.x > origin.x + size.x) vec.x = origin.x + size.x;

	if (vec.y < origin.y) vec.y = origin.y;
	else if (vec.y > origin.y + size.y) vec.y = origin.y + size.y;

	return vec;
}
