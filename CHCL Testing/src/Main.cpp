#include <iostream>

#include "CHCL.h"
#include "VectorN.h"
#include "Vector2.h"

int main()
{
	chcl::VectorN<2> Vector1(5.f);

	std::cout << "Template vector: [x: " << Vector1.position[0] << ", y: " << Vector1.position[1] << "]\n";

	chcl::Vector2 Vector2_1(3.f), Vector2_2(5.f);
	
	std::cout << "Template vector2: [x: " << Vector2_1.x << ", y: " << Vector2_1.y << "]\n";

	std::cout << "CHCL Vector2 print: ";
	chcl::printVector(Vector2_2);
	std::cout << '\n';

	chcl::VectorN<5> Vector5d1, Vector5d2(4.2f), Vector5d3{ 0.1f, -3.7f, 17.73f, 2.957f, -175.9f };

	std::cout << "5D Vector 1: "; chcl::printVector(Vector5d1);
	std::cout << "5D Vector 2: "; chcl::printVector(Vector5d2);
	std::cout << "5D Vector 3: "; chcl::printVector(Vector5d3);
	std::cout << "5D Vector 2 + 3: "; chcl::printVector(Vector5d2 + Vector5d3);
	std::cout << "5D Vector 2 x 2: "; chcl::printVector(Vector5d2 * 2);
	std::cout << "5D Vector 2 / 3: "; chcl::printVector(Vector5d3 / 3);

	std::cout << "5D Vector 3 as Matrix:\n";
	chcl::printMatrix(Vector5d3.toMatrix());
	std::cout << '\n';

	chcl::Vector2 vec1, vec2(3), vec3{ 5, 1 },
		vec4(vec2 + vec3), vec5(vec4.normalised()), vec6(vec2.normalised());

	std::cout << "Vector2 #1"; printVector(vec1);
	std::cout << "Vector2 #2:"; printVector(vec2);
	std::cout << "Vector2 #3:"; printVector(vec3);
	std::cout << "Vector2 #2 + #3:"; printVector(vec2 + vec3);
	std::cout << "Vector2 #4:"; printVector(vec4);
	std::cout << "Vector2 #4 normalised:"; printVector(vec5);
	std::cout << "Vector2 #2 normalised:"; printVector(vec6);

	std::cout << "Vector2 as Matrix:\n";
	chcl::printMatrix(vec5.toMatrix());

	float vals[] = { 0.482251f, -4.62f, 19, 42069, -729, 100.99f };
	chcl::Matrix matrix1, matrix2(3, 2), matrix3(2, 4, 3.f), matrix4(4, 5, 6.f),
		matrix5(2, 3, vals);

	std::cout << '\n';
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
	chcl::printVector(chcl::VectorN<6>::FromMatrix(chcl::Matrix{ 1, 6, vals }));

	chcl::Matrix matrix6(2, 3);
	matrix6 = {
		0.5f, 0.2f,
		0.3f, 1.3f,
		-2.1f, 0.007f
	};
	std::cout << "\n\nMatrices from initializer lists:\n";
	chcl::printMatrix(matrix6);

	chcl::Matrix matrix7(4, 3, {
			0.4f, 1.4f, 4.7f, 0.09f,
			-7.5f, 11.92f, -109.775f, 60.f,
			31.8f, 12.9f, -47.f, -0.038f
		});
	std::cout << '\n';
	chcl::printMatrix(matrix7);
}