#pragma once

#include "VectorN.h"

namespace chcl
{
	struct Vector3 : public VectorN<3>
	{
		using VectorN::VectorN;

		float &x = position[0],
			&y = position[1],
			&z = position[2];

		Vector3(float x, float y, float z);

		Vector3(const VectorN<3>& vec);

		inline Vector3 xComponent() const { return component(0); }
		inline Vector3 yComponent() const { return component(1); }
		inline Vector3 zComponent() const { return component(2); }
	};
}