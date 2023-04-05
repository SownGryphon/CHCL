#pragma once

#include "Matrix.h"
#include "tVectorN.h"
#include "tVector2.h"
#include "tVector3.h"

namespace chcl
{

	template <unsigned int dims>
	void printVector(const tVectorN<dims>& vec)
	{
		std::cout << '[';

		for (unsigned int i = 0; i < dims; ++i)
		{
			if (i)
			{
				std::cout << ", ";
			}

			std::cout << vec.position[i];
		}

		std::cout << "]\n";
	}

	void printVector(const tVector2& vec);
	void printVector(const tVector3& vec);

	void printMatrix(const Matrix& matrix, unsigned int places = 5);
}