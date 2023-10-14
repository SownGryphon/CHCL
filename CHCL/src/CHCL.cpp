#include "CHCL.h"

#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>

using namespace chcl;

void chcl::printMatrix(const Matrix &matrix, unsigned int places)
{
	std::stringstream numStream;
	size_t maxLen = 0;
	for (unsigned int i = 0; i < matrix.getRows(); ++i)
	{
		for (unsigned int j = 0; j < matrix.getCols(); ++j)
		{
			numStream.str(std::string());
			numStream << std::fixed << std::setprecision(places) << matrix.at(j, i);

			if (numStream.str().length() > maxLen)
				maxLen = numStream.str().length();
		}
	}

	for (unsigned int i = 0; i < matrix.getRows(); ++i)
	{
		std::cout << '|';

		for (unsigned int j = 0; j < matrix.getCols(); ++j)
		{
			if (j != 0)
				std::cout << ", ";

			std::cout << std::fixed << std::setw(maxLen) << std::setprecision(places) << matrix.at(j, i);
		}

		std::cout << "|\n";
	}
}