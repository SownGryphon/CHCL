#pragma once

#include "chcl/maths/SquareMatrix.h"

namespace chcl
{
	using Mat3 = SquareMatrix<3, float>;

	template <>
	class Matrix<3, 3, float> : public SquareMatrixBase<3, float, Matrix>
	{
	public:
		using SquareMatrixBase<3, float, Matrix>::SquareMatrixBase;

		static Matrix<3, 3, float> RotationXY(float radians);
		static Matrix<3, 3, float> RotationXZ(float radians);
		static Matrix<3, 3, float> RotationYZ(float radians);
		static Matrix<3, 3, float> Rotation3D(float pitch, float yaw);
	};
}