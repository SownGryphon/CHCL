#include "Vector2.h"

#include <cmath>

using namespace chcl;

float Vector2::arg() const
{
	return atan2f(y, x);
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const VectorN<2>& vec) :
	VectorN{ vec } {}

Vector2 Vector2::xComponent() const
{
	return component(0);
}

Vector2 Vector2::yComponent() const
{
	return component(1);
}