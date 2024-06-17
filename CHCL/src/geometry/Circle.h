#pragma once

#include "Shape.h"

namespace chcl
{
	struct Circle : public Shape
	{
		Vector2<> origin;
		float r;

		Circle(float x, float y, float r);
		Circle(const Vector2<> &origin, float r);

		virtual bool containsPoint(Vector2<float> point) const override;
		virtual Vector2<float> constrainPoint(Vector2<float> point) const override;
	};
}