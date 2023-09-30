#include "Vector3.h"

using namespace chcl;

Vector3::Vector3(float x, float y, float z)
{
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
}

Vector3::Vector3(const VectorN<3>& vec) :
	VectorN{ vec } {}