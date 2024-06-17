#include "SquareMatrix.h"

#include "../geometry/Vector3.h"

namespace chcl
{
	Mat2 Matrix<2, 2, float>::Rotation(float angle)
	{
		return Mat2({
			std::cos(angle), -std::sin(angle),
			std::sin(angle),  std::cos(angle)
		});
	}

	Mat3 Matrix<3, 3, float>::RotationXY(float angle)
	{
		return Mat3({
			std::cos(angle), -std::sin(angle), 0.f,
			std::sin(angle),  std::cos(angle), 0.f,
			0.f, 0.f, 1.f
		});
	}

	Mat3 Matrix<3, 3, float>::RotationXZ(float angle)
	{
		return Mat3({
			std::cos(angle), 0.f, -std::sin(angle),
			0.f, 1.f, 0.f,
			std::sin(angle), 0.f,  std::cos(angle),
		});
	}

	Mat3 Matrix<3, 3, float>::RotationYZ(float angle)
	{
		return Mat3({
			1.f, 0.f, 0.f,
			0.f, std::cos(angle), -std::sin(angle),
			0.f, std::sin(angle),  std::cos(angle)
		});
	}

	Mat3 Matrix<3, 3, float>::Rotation3D(float pitch, float yaw)
	{
		// Applying pitch then yaw
		return Mat3({
			std::cos(yaw), -std::cos(pitch) * std::sin(yaw), std::sin(pitch) * std::sin(yaw),
			std::sin(yaw), std::cos(pitch) * std::cos(yaw), -std::sin(pitch) * std::cos(yaw),
			0, std::sin(pitch), std::cos(pitch)
		});
	}

	Mat4 Matrix<4, 4, float>::Ortho(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
		Vector3<float> scaling(2 / (xMax - xMin), 2 / (yMax - yMin), 2 / (zMax - zMin));

		return Mat4({
			scaling.x, 0, 0, -(xMin + xMax) / 2 * scaling.x,
			0, scaling.y, 0, -(yMin + yMax) / 2 * scaling.y,
			0, 0, scaling.z, -(zMin + zMax) / 2 * scaling.z,
			0, 0, 0, 1
		});
	}

	Mat4 Matrix<4, 4, float>::Translation3D(float x, float y, float z)
	{
		return Mat4({
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		});
	}

	Mat4 Matrix<4, 4, float>::Translation3D(Vector3<float> pos)
	{
		return Mat4({
			1, 0, 0, pos.x,
			0, 1, 0, pos.y,
			0, 0, 1, pos.z,
			0, 0, 0, 1
		});
	}

	Mat4 Matrix<4, 4, float>::Scale3D(float x, float y, float z)
	{
		return Mat4({
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		});
	}

	Mat4 Matrix<4, 4, float>::Scale3D(Vector3<float> size)
	{
		return Mat4({
			size.x, 0, 0, 0,
			0, size.y, 0, 0,
			0, 0, size.z, 0,
			0, 0, 0, 1
		});
	}

	Mat4 Matrix<4, 4, float>::RotationXY(float angle)
	{
		return Mat4({
			std::cos(angle), -std::sin(angle), 0, 0,
			std::sin(angle), std::cos(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		});
	}
}