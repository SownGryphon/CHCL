#pragma once

#include "SquareMatrix.h"

namespace chcl
{
	using Mat2 = SquareMatrix<2, float>;

	template <>
	class Matrix<2, 2, float> : public SquareMatrixBase<2, float, Matrix>
	{
	public:
		using SquareMatrixBase<2, float, Matrix>::SquareMatrixBase;

		static Matrix<2, 2, float> Rotation(float angle);
	};
}