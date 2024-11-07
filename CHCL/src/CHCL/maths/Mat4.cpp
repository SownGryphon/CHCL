#include "Mat4.h"

chcl::Mat4 chcl::Matrix<4, 4, float>::Ortho(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	Vector3<float> scaling(2 / (xMax - xMin), 2 / (yMax - yMin), 2 / (zMax - zMin));

	return Mat4({
		scaling.x, 0, 0, -(xMin + xMax) / 2 * scaling.x,
		0, scaling.y, 0, -(yMin + yMax) / 2 * scaling.y,
		0, 0, scaling.z, -(zMin + zMax) / 2 * scaling.z,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::Translation3D(float x, float y, float z)
{
	return Mat4({
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::Translation3D(Vector3<float> pos)
{
	return Mat4({
		1, 0, 0, pos.x,
		0, 1, 0, pos.y,
		0, 0, 1, pos.z,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::Scale3D(float x, float y, float z)
{
	return Mat4({
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::Scale3D(Vector3<float> size)
{
	return Mat4({
		size.x, 0, 0, 0,
		0, size.y, 0, 0,
		0, 0, size.z, 0,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::RotationXY(float rads)
{
	return Mat4({
		std::cos(rads), -std::sin(rads), 0, 0,
		std::sin(rads),  std::cos(rads), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::RotationXZ(float rads)
{
	return Mat4({
		std::cos(rads), 0, -std::sin(rads), 0,
		0, 1, 0, 0,
		std::sin(rads), 0,  std::cos(rads), 0,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::RotationYZ(float rads)
{
	return Mat4({
		1, 0, 0, 0,
		0, std::cos(rads), -std::sin(rads), 0,
		0, std::sin(rads),  std::cos(rads), 0,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::Rotation3D(float pitch, float yaw)
{
	// Applying pitch then yaw
	return Mat4({
		std::cos(yaw), -std::cos(pitch) * std::sin(yaw), std::sin(pitch) * std::sin(yaw), 0,
		std::sin(yaw), std::cos(pitch) * std::cos(yaw), -std::sin(pitch) * std::cos(yaw), 0,
		0, std::sin(pitch), std::cos(pitch), 0,
		0, 0, 0, 1
	});
}

chcl::Mat4 chcl::Matrix<4, 4, float>::Rotation3D(Quaternion rot)
{
	/* Converting a quaternion representing a 3D rotation to a rotation matrix
	* https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix
	*/
	float s = 1.f / (rot.normSq());
	return Mat4({
		1.f - 2.f * s * (rot.j * rot.j + rot.k * rot.k), 2.f * s * (rot.i * rot.j - rot.k * rot.re), 2.f * s * (rot.i * rot.k + rot.j * rot.re), 0.f,
		2.f * s * (rot.i * rot.j + rot.k * rot.re), 1.f - 2.f * s * (rot.i * rot.i + rot.k * rot.k), 2.f * s * (rot.j * rot.k - rot.i * rot.re), 0.f,
		2.f * s * (rot.i * rot.k - rot.j * rot.re), 2.f * s * (rot.j * rot.k + rot.i * rot.re), 1.f - 2.f * s * (rot.i * rot.i + rot.j * rot.j), 0.f,
		0.f, 0.f, 0.f, 1.f
	});
}