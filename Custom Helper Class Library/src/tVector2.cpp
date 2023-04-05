#include "include/tVector2.h"

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

tVector2 tVector2::xComponent() const
{
	return component(0);
}

tVector2 tVector2::yComponent() const
{
	return component(1);
}