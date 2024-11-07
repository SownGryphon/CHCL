#include "Mat2.h"

chcl::Mat2 chcl::Matrix<2, 2, float>::Rotation(float angle)
{
	return Mat2({
		std::cos(angle), -std::sin(angle),
		std::sin(angle),  std::cos(angle)
	});
}