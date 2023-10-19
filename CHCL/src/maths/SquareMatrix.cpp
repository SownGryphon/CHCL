#include "SquareMatrix.h"

#include "../geometry/Vector3.h"

namespace chcl
{
	Mat2 Mat2::Rotation(float angle)
	{
		return Mat2({
			std::cos(angle), -std::sin(angle),
			std::sin(angle),  std::cos(angle)
		});
	}

	Mat4 Mat4::Ortho(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
		Vector3<float> scaling(2 / (xMax - xMin), 2 / (yMax - yMin), 2 / (zMax - zMin));

		return Mat4({
			scaling.x, 0, 0, -(xMin + xMax) / 2 * scaling.x,
			0, scaling.y, 0, -(yMin + yMax) / 2 * scaling.y,
			0, 0, scaling.z, -(zMin + zMax) / 2 * scaling.z,
			0, 0, 0, 1
		});
	}

	Mat4 Mat4::Translation(float x, float y, float z)
	{
		return Mat4({
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		});
	}

	Mat4 Mat4::Scale(float x, float y, float z)
	{
		return Mat4({
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		});
	}

	Mat4 Mat4::Rotation2D(float angle)
	{
		return Mat4({
			std::cos(angle), -std::sin(angle), 0, 0,
			std::sin(angle), std::cos(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		});
	}
}