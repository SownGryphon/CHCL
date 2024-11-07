#pragma once

#include "chcl/maths/SquareMatrix.h"

#include "chcl/geometry/Vector3.h"
#include "chcl/geometry/Quaternion.h"

namespace chcl
{
	using Mat4 = SquareMatrix<4, float>;

	template <>
	class Matrix<4, 4, float> : public SquareMatrixBase<4, float, Matrix>
	{
	public:
		using SquareMatrixBase<4, float, Matrix>::SquareMatrixBase;

		static Matrix<4, 4, float> Ortho(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
		static Matrix<4, 4, float> Translation3D(float x, float y, float z);
		static Matrix<4, 4, float> Translation3D(Vector3<float> pos);
		static Matrix<4, 4, float> Scale3D(float x, float y, float z);
		static Matrix<4, 4, float> Scale3D(Vector3<float> size);
		static Matrix<4, 4, float> RotationXY(float radians);
		static Matrix<4, 4, float> RotationXZ(float radians);
		static Matrix<4, 4, float> RotationYZ(float radians);
		static Matrix<4, 4, float> Rotation3D(float pitch, float yaw);
		static Matrix<4, 4, float> Rotation3D(Quaternion rotation);
	};
}