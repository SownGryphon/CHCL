#pragma once

#include "Shape.h"

namespace chcl
{
	struct Rect : public Shape
	{
		Vector2 origin, size;

		Rect() {};
		Rect(float x, float y, float width, float height);
		Rect(const Vector2 &origin, const Vector2 &size);

		inline float top() const { return origin.y + size.y; }
		inline float bottom() const { return origin.y; }
		inline float left() const { return origin.x; }
		inline float right() const { return origin.x + size.x; }
		inline Vector2 center() const { return origin + size / 2; }

		virtual bool containsPoint(const Vector2 &vec) const;
		virtual Vector2 constrainPoint(Vector2 vec) const;
	};
}