#include "Common.h"

float chcl::toRadians(float degrees)
{
	return degrees / 180 * PI;
}

float chcl::toDegrees(float radians)
{
	return radians / PI * 180;
}