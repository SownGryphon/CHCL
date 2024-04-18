#include "Prints.h"

void chcl::printVector(const DynamicVector &vec)
{
	std::cout << '[';
	for (unsigned int i = 0; i < vec.size(); ++i)
	{
		if (i)
			std::cout << ", ";
		std::cout << vec[i];
	}
	std::cout << "]\n";
}

void chcl::printMatrix(const DynamicMatrix &mat)
{
	// TODO: Dynamic matrix print
	std::cout << "Imagine a matrix was printed here:\n";
}