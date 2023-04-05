#pragma once

#include "tVectorN.h"

namespace chcl
{
	struct tVector3 : public tVectorN<3>
	{
		using tVectorN::tVectorN;

		float &x = position[0],
			&y = position[1],
			&z = position[2];

		tVector3(float x, float y, float z);

		tVector3(const tVectorN<3>& vec);

		tVector3 xComponent() const;
		tVector3 yComponent() const;
		tVector3 zComponent() const;
	};
}