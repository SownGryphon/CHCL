#include "Rect.h"

using namespace chcl;

Rect::Rect(float x, float y, float width, float height)
	: origin(x, y), size(width, height) {}

Rect::Rect(const Vector2 &origin, const Vector2 &size)
	: origin(origin), size(size) {}

bool Rect::containsPoint(const Vector2 &vec) const
{
	return vec.x >= origin.x && vec.x <= origin.x + size.x
		&& vec.y >= origin.y && vec.y <= origin.y + size.y;
}

Vector2 Rect::constrainPoint(Vector2 vec) const
{
	if (vec.x < origin.x) vec.x = origin.x;
	else if (vec.x > origin.x + size.x) vec.x = origin.x + size.x;

	if (vec.y < origin.y) vec.y = origin.y;
	else if (vec.y > origin.y + size.y) vec.y = origin.y + size.y;

	return vec;
}
