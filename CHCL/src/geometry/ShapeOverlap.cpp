#include "ShapeOverlap.h"

using namespace chcl;

template <>
bool chcl::checkOverlap(const Circle &c1, const Circle &c2)
{
	return (c1.origin - c2.origin).magsq() <= std::powf(c1.r + c2.r, 2);
}

template <>
bool chcl::checkOverlap(const Circle &circle, const Rect &rect)
{
	return circle.containsPoint(rect.constrainPoint(circle.origin));
}

template <>
bool chcl::checkOverlap(const Rect &r1, const Rect &r2)
{
	return r1.origin.x + r1.size.x > r2.origin.x
		&& r2.origin.x + r2.size.x > r1.origin.x
		&& r1.origin.y + r1.size.y > r2.origin.y
		&& r2.origin.y + r2.size.y > r1.origin.y;
}