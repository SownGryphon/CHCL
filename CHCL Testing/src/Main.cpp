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

	chcl::VectorN<5> Vector5_1, Vector5_2(4.2f), Vector5_3{ 0.1f, -3.7f, 17.73f, 2.957f, -175.9f };

	std::cout << "5D Vector #1: "; chcl::printVector(Vector5_1);
	std::cout << "5D Vector #2: "; chcl::printVector(Vector5_2);
	std::cout << "5D Vector #3: "; chcl::printVector(Vector5_3);
	std::cout << "5D Vectors #2 + #3: "; chcl::printVector(Vector5_2 + Vector5_3);
	std::cout << "5D Vector #2 x 2: "; chcl::printVector(Vector5_2 * 2);
	std::cout << "5D Vector #3 / 3: "; chcl::printVector(Vector5_3 / 3);

	std::cout << "5D Vector #3 as Matrix:\n";
	chcl::printMatrix(Vector5_3.toMatrix());
	std::cout << '\n';

	chcl::Vector2 vec1, vec2(3), vec3{ 5, 1 },
		vec4(vec2 + vec3), vec5(vec4.normalised()), vec6(vec2.normalised());

	std::cout << "Vector2 #1 (blank): "; printVector(vec1);
	std::cout << "Vector2 #2 (from 3): "; printVector(vec2);
	std::cout << "Vector2 #3 (from {5, 1}): "; printVector(vec3);
	std::cout << "Vector2 #2 + #3: "; printVector(vec2 + vec3);
	std::cout << "Vector2 #4 (from vec2 + vec3): "; printVector(vec4);
	std::cout << "Vector2 #5 (vec4 normalised): "; printVector(vec5);
	std::cout << "Vector2 #6 (vec2 normalised): "; printVector(vec6);

	std::cout << "Vector2 #5 as Matrix:\n"; chcl::printMatrix(vec5.toMatrix());

	float vals[] = { 0.482251f, -4.62f, 19, 42069, -729, 100.99f };
	chcl::Matrix matrix1, matrix2(3, 2), matrix3(2, 4, 3.f), matrix4(4, 5, 6.f),
		matrix5(2, 3, vals);

	std::cout << "\nMatrix #1 (blank):\n"; chcl::printMatrix(matrix1);
	std::cout << "Matrix #2 (3x2):\n"; chcl::printMatrix(matrix2);
	std::cout << "Matrix #3 (2x4, default 3.f):\n"; chcl::printMatrix(matrix3);
	std::cout << "Matrix #4 (4x5, default 6.f):\n"; chcl::printMatrix(matrix4);
	std::cout << "Matrix #5 (from float array):\n"; chcl::printMatrix(matrix5, 8);
	std::cout << "Matrix #4 * #3:\n"; chcl::printMatrix(matrix4 * matrix3);

	std::cout << "\nMatrix as 6D Vector (same values as Matrix #5): ";
	chcl::printVector(chcl::VectorN<6>::FromMatrix(chcl::Matrix{ 1, 6, vals }));

	std::cout << "\nMatrices from initializer lists:\n";
	chcl::Matrix matrix6(2, 3, {
		0.5f, 0.2f,
		0.3f, 1.3f,
		-2.1f, 0.007f
	});
	std::cout << "Matrix6:\n"; chcl::printMatrix(matrix6);

	chcl::Matrix matrix7(3, 4, {
			0.4f, 1.4f, 4.7f,
			0.09f, -7.5f, 11.92f,
			-109.775f, 60.f, 31.8f,
			12.9f, -47.f, -0.038f
		});
	std::cout << "Matrix7:\n"; chcl::printMatrix(matrix7);

	std::cout << "Matrix7 * Matrix6:\n"; chcl::printMatrix(matrix7 * matrix6);

	std::cout << "\nMatrix determinants:\n";
	chcl::Matrix detMatrix1(2, 2, {
			4, 6,
			3, 8
		});
	std::cout << "Matrix 1:\n"; chcl::printMatrix(detMatrix1);
	std::cout << "Determinant: " << detMatrix1.determinant() << "\n\n";

	chcl::Matrix detMatrix2(3, 3, {
			6, 1, 1,
			4, -2, 5,
			2, 8, 7
		});
	std::cout << "Matrix 2:\n"; chcl::printMatrix(detMatrix2);
	std::cout << "Determinant: " << detMatrix2.determinant() << "\n\n";
}