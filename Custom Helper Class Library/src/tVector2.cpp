#include "includes/tVector2.h"

#include <cmath>

using namespace chcl;

float tVector2::arg() const
{
	return atan2f(y, x);
}

tVector2::tVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

tVector2::tVector2(const tVectorN<2>& vec) :
	tVectorN{ vec } {}