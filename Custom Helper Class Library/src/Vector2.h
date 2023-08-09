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

		Vector2 xComponent() const;
		Vector2 yComponent() const;

		float arg() const;
	};
}