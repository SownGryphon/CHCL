#include "Mat3.h"

chcl::Mat3 chcl::Matrix<3, 3, float>::RotationXY(float rads)
{
	return Mat3({
		std::cos(rads), -std::sin(rads), 0.f,
		std::sin(rads),  std::cos(rads), 0.f,
		0.f, 0.f, 1.f
	});
}

chcl::Mat3 chcl::Matrix<3, 3, float>::RotationXZ(float rads)
{
	return Mat3({
		std::cos(rads), 0.f, -std::sin(rads),
		0.f, 1.f, 0.f,
		std::sin(rads), 0.f,  std::cos(rads),
	});
}

chcl::Mat3 chcl::Matrix<3, 3, float>::RotationYZ(float rads)
{
	return Mat3({
		1.f, 0.f, 0.f,
		0.f, std::cos(rads), -std::sin(rads),
		0.f, std::sin(rads),  std::cos(rads)
	});
}

chcl::Mat3 chcl::Matrix<3, 3, float>::Rotation3D(float pitch, float yaw)
{
	// Applying pitch then yaw
	return Mat3({
		std::cos(yaw), -std::cos(pitch) * std::sin(yaw), std::sin(pitch) * std::sin(yaw),
		std::sin(yaw), std::cos(pitch) * std::cos(yaw), -std::sin(pitch) * std::cos(yaw),
		0, std::sin(pitch), std::cos(pitch)
	});
}