#include <iostream>

#include "CHCL.h"
#include "tVectorN.h"
#include "tVector2.h"
#include "Vector2.h"

int main()
{
	chcl::tVectorN<2> tVector1{ 5.f };

	std::cout << "Template vector: [x: " << tVector1.position[0] << ", y: " << tVector1.position[1] << "]\n";

	chcl::tVector2 tVector2_1{ 3.f }, tVector2_2{ 5.f };
	
	std::cout << "Template vector2: [x: " << tVector2_1.x << ", y: " << tVector2_1.y << "]\n";

	std::cout << "CHCL tVector2 print: ";
	chcl::printVector(tVector2_2);


	chcl::tVectorN<5> tVector5d1{}, tVector5d2{ 4.2f }, tVector5d3{ { 0.1f, -3.7f, 17.73f, 2.957f, -175.9f } };

	std::cout << "5D Vector 1: "; chcl::printVector(tVector5d1);
	std::cout << "5D Vector 2: "; chcl::printVector(tVector5d2);
	std::cout << "5D Vector 3: "; chcl::printVector(tVector5d3);
	std::cout << "5D Vector 2 + 3: "; chcl::printVector(tVector5d2 + tVector5d3);
	std::cout << "5D Vector 2 x 2: "; chcl::printVector(tVector5d2 * 2);
	std::cout << "5D Vector 2 / 3: "; chcl::printVector(tVector5d3 / 3);

	std::cout << "5D Vector 3 as Matrix:\n";
	chcl::printMatrix(tVector5d3.toMatrix());

	chcl::tVector2 vec1, vec2{ 3 }, vec3{ 5, 1 },
		vec4{ vec2 + vec3 }, vec5{ vec4.normalised() }, vec6{ vec2.normalised() };

	printVector(vec1);
	printVector(vec2);
	printVector(vec3);
	printVector(vec2 + vec3);
	printVector(vec4);
	printVector(vec5);
	printVector(vec6);

	std::cout << "tVector2 as Matrix:\n";
	chcl::printMatrix(vec5.toMatrix());

	float vals[] = { 0.482251f, -4.62f, 19, 42069, -729, 100.99f };
	chcl::Matrix matrix1{}, matrix2{ 3, 2 }, matrix3{ 2, 4, 3.f }, matrix4(4, 5, 6.f),
		matrix5{2, 3, vals};

	chcl::printMatrix(matrix1);
	std::cout << '\n';
	chcl::printMatrix(matrix2);
	std::cout << '\n';
	chcl::printMatrix(matrix3);
	std::cout << '\n';
	chcl::printMatrix(matrix4);
	std::cout << '\n';
	chcl::printMatrix(matrix5, 8);
	std::cout << '\n';
	chcl::printMatrix(matrix4 * matrix3);

	std::cout << "\n\nMatrix as 6D Vector:";
	chcl::printVector(chcl::tVectorN<6>::fromMatrix(chcl::Matrix{ 1, 6, vals }));
}