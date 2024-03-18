#pragma once

#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>

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

	template <unsigned int width, unsigned int height>
	void printMatrix(const Matrix<width, height> &matrix, unsigned int places = 2)
	{
		std::stringstream numStream;
		size_t maxLen = 0;
		for (unsigned int i = 0; i < height; ++i)
		{
			for (unsigned int j = 0; j < width; ++j)
			{
				numStream.str(std::string());
				numStream << std::fixed << std::setprecision(places) << matrix.at(j, i);

				if (numStream.str().length() > maxLen)
					maxLen = numStream.str().length();
			}
		}

		for (unsigned int i = 0; i < height; ++i)
		{
			std::cout << '|';

			for (unsigned int j = 0; j < width; ++j)
			{
				if (j != 0)
					std::cout << ", ";

				std::cout << std::fixed << std::setw(maxLen) << std::setprecision(places) << matrix.at(j, i);
			}

			std::cout << "|\n";
		}
	}
}