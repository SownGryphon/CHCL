#pragma once

#include "chcl/geometry/Vector2.h"
#include "chcl/geometry/Shape.h"
#include "chcl/geometry/AlignedRect.h"

namespace chcl
{
	struct Rect : public Shape
	{
		Rect() : m_center(), m_size(), m_rotation() {}
		Rect(Vector2<float> center, Vector2<float> size, float rotation) : m_center(center), m_size(size), m_rotation(rotation) {}
		Rect(const AlignedRect &rect) : m_center(rect.center()), m_size(rect.size), m_rotation(0.f) {}

		virtual bool containsPoint(Vector2<float> point) const override;
		virtual Vector2<float> constrainPoint(Vector2<float> point) const override;

		Vector2<float> m_center, m_size;
		float m_rotation;
	};
}