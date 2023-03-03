#include <iomanip>
#include <ios>
#include <iostream>

#include "includes/CHCL.h"

using namespace chcl;

void chcl::printVector(const tVector2& vec)
{
	std::cout << "[x: " << vec.x << ", y: " << vec.y << "]\n";
}

void chcl::printVector(const tVector3& vec)
{
	std::cout << "[x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << "]\n";
}

void chcl::printMatrix(const Matrix& matrix, unsigned int places)
{
	for (unsigned int i = 0; i < matrix.getRows(); ++i)
	{
		std::cout << '|';

		for (unsigned int j = 0; j < matrix.getCols(); ++j)
		{
			if (j != 0)
			{
				std::cout << ", ";
			}

			std::cout << std::setw(places) << matrix.getValue(j, i);
		}

		std::cout << "|\n";
	}
}