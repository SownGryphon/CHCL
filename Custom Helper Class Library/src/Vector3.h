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
		Vector3(const Vector3 &vec);

		//inline float x() const { return position[0]; }
		//inline float y() const { return position[1]; }
		//inline float z() const { return position[2]; }

		//inline float& x() { return position[0]; }
		//inline float& y() { return position[1]; }
		//inline float& z() { return position[2]; }

		inline Vector3 xComponent() const { return component(0); }
		inline Vector3 yComponent() const { return component(1); }
		inline Vector3 zComponent() const { return component(2); }
	};
}