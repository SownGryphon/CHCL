#pragma once

#include "Shape.h"

namespace chcl
{
	struct Rect : public Shape
	{
		Vector2 origin, size;

		Rect(float x, float y, float width, float height);
		Rect(const Vector2 &origin, const Vector2 &size);

		virtual bool containsPoint(const Vector2 &vec) const;
		virtual Vector2 constrainPoint(Vector2 vec) const;
	};
}