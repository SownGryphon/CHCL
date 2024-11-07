#include "Circle.h"

using namespace chcl;

Circle::Circle(float x, float y, float r)
	: origin(x, y), r(r) {}

Circle::Circle(const Vector2<> &origin, float r)
	: origin(origin), r(r) {}

bool Circle::containsPoint(Vector2<float> point) const
{
	return (origin - point).magsq() <= std::powf(r, 2);
}

Vector2<float> Circle::constrainPoint(Vector2<float> point) const
{
	Vector2 offset = point - origin;
	if (offset.magsq() <= std::powf(r, 2)) return point;

	offset *= r / offset.mag();
	return origin + offset;
}
