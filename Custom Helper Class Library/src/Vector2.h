#pragma once

#include "VectorN.h"

namespace chcl
{
	struct Vector2 : public VectorN<2>
	{
		using VectorN::VectorN;

		float &x = position[0],
			&y = position[1];

		Vector2(float x, float y);

		Vector2(const VectorN<2>& vec);

		inline Vector2 xComponent() const { return component(0); }
		inline Vector2 yComponent() const { return component(1); }

		float arg() const;
	};
}