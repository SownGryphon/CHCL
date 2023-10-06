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

Vector3::Vector3(const Vector3 &vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

Vector3 Vector3::Cross(const Vector3 & vec1, const Vector3 & vec2)
{
	return Vector3(
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.x * vec2.z - vec1.z * vec2.x,
		vec1.x * vec2.y - vec1.y * vec2.x
	);
}