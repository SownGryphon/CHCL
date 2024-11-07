#include "MatrixTests.h"

#include <chcl/maths/Matrix.h>
#include <chcl/maths/SquareMatrix.h>

void MatrixTestsAll()
{
	chcl::Matrix<3, 3> testMat;
	testMat.determinant();
}