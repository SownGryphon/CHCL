#pragma once

#include "VectorN.h"

namespace chcl
{
	struct Vector2 : public VectorN<2>
	{
		using VectorN::VectorN;

		Vector2(float x, float y);
		Vector2(const VectorN<2>& vec);

		static Vector2 FromAngle(float angle);

		inline float x() const { return position[0]; }
		inline float y() const { return position[1]; }

		inline float& x() { return position[0]; }
		inline float& y() { return position[1]; }

		inline Vector2 xComponent() const { return component(0); }
		inline Vector2 yComponent() const { return component(1); }

		float arg() const;
	};
}