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