#include "Circle.h"

using namespace chcl;

Circle::Circle(float x, float y, float r)
	: origin(x, y), r(r) {}

Circle::Circle(const Vector2 &origin, float r)
	: origin(origin), r(r) {}

bool Circle::containsPoint(const Vector2 &vec) const
{
	return (origin - vec).magsq() <= std::powf(r, 2);
}

Vector2 Circle::constrainPoint(Vector2 vec) const
{
	Vector2 offset = vec - origin;
	if (offset.magsq() <= std::powf(r, 2)) return vec;

	offset *= r / offset.mag();
	return origin + offset;
}
