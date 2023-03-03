#include "includes/tVector3.h"

using namespace chcl;

tVector3::tVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

tVector3::tVector3(const tVectorN<3>& vec) :
	tVectorN{ vec } {}

tVector3 tVector3::xComponent() const
{
	return component(0);
}

tVector3 tVector3::yComponent() const
{
	return component(1);
}

tVector3 tVector3::zComponent() const
{
	return component(2);
}