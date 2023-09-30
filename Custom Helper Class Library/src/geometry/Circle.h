#pragma once

#include "Shape.h"

namespace chcl
{
	struct Circle : public Shape
	{
		Vector2 origin;
		float r;

		Circle(float x, float y, float r);
		Circle(const Vector2 &origin, float r);

		virtual bool containsPoint(const Vector2 &vec) const;
		virtual Vector2 constrainPoint(Vector2 vec) const;
	};
}