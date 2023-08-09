#include "Vector3.h"

using namespace chcl;

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const VectorN<3>& vec) :
	VectorN{ vec } {}