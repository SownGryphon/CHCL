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

		tVector2 xComponent() const;
		tVector2 yComponent() const;

		float arg() const;
	};
}