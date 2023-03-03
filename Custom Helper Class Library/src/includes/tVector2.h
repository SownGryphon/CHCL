#pragma once

#include "tVectorN.h"

namespace chcl
{
	struct tVector2 : public tVectorN<2>
	{
		using tVectorN::tVectorN;

		float &x = position[0],
			&y = position[1];

		tVector2(float x, float y);

		tVector2(const tVectorN<2>& vec);

		float arg() const;
	};
}