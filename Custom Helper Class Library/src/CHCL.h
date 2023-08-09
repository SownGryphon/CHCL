#pragma once

#include <iostream>

#include "Matrix.h"
#include "VectorN.h"
#include "Vector2.h"
#include "Vector3.h"

namespace chcl
{

	template <unsigned int dims>
	void printVector(const VectorN<dims>& vec)
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

	inline void printVector(const VectorN<2>& vec)
	{
		std::cout << "[x: " << vec.position[0] << ", y: " << vec.position[1] << "]\n";
	}

	inline void printVector(const VectorN<3>& vec)
	{
		std::cout << "[x: " << vec.position[0] << ", y: " << vec.position[1] << ", z:" << vec.position[2] << "]\n";
	}

	void printMatrix(const Matrix& matrix, unsigned int places = 2);
}