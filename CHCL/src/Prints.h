#pragma once

#include <iostream>

#include "maths/Matrix.h"
#include "geometry/VectorN.h"

namespace chcl
{

	template <unsigned int dims, typename T>
	void printVector(const VectorN<dims, T> &vec)
	{
		std::cout << '[';

		for (unsigned int i = 0; i < dims; ++i)
		{
			if (i)
			{
				std::cout << ", ";
			}

			std::cout << vec[i];
		}

		std::cout << "]\n";
	}

	template <typename T>
	void printVector(const VectorN<2, T> &vec)
	{
		std::cout << "[x: " << vec[0] << ", y: " << vec[1] << "]\n";
	}

	template <typename T>
	void printVector(const VectorN<3, T> &vec)
	{
		std::cout << "[x: " << vec[0] << ", y: " << vec[1] << ", z:" << vec[2] << "]\n";
	}

	void printMatrix(const Matrix &matrix, unsigned int places = 2);
}