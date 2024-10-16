#pragma once

#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>

#include "maths/Matrix.h"
#include "maths/DynamicMatrix.h"

#include "geometry/VectorN.h"
#include "geometry/DynamicVector.h"

namespace chcl
{
	template <unsigned int width, unsigned int height, typename T = float>
	void printMatrix(const Matrix<width, height, T> &matrix, unsigned int places = 2)
	{
		std::stringstream numStream;
		size_t maxLen = 0;
		for (unsigned int i = 0; i < height; ++i)
		{
			for (unsigned int j = 0; j < width; ++j)
			{
				numStream.str(std::string());
				numStream << std::fixed << std::setprecision(places) << matrix.at(i, j);

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

				std::cout << std::fixed << std::setw(maxLen) << std::setprecision(places) << matrix.at(i, j);
			}

			std::cout << "|\n";
		}
	}

	template <typename T>
	void printMatrix(const DynamicMatrix<T> &mat)
	{
		std::cout << "Imagine this is nicely printed:\n";
		for (size_t i = 0; i < mat.rows(); ++i)
		{
			std::cout << "| ";
			for (size_t j = 0; j < mat.cols(); ++j)
			{
				if (j)
					std::cout << ", ";
				std::cout << mat.at(i, j);
			}
			std::cout << " |\n";
		}
	}
}