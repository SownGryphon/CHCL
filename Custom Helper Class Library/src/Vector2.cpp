#include "Vector2.h"

#include <cmath>

using namespace chcl;

float Vector2::arg() const
{
	return atan2f(y(), x());
}

Vector2::Vector2(float x, float y)
{
	this->position[0] = x;
	this->position[1] = y;
}

Vector2::Vector2(const VectorN<2>& vec) :
	VectorN{ vec } {}