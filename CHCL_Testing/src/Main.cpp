#include <algorithm>
#include <iostream>
#include <vector>

#include "Prints.h"

#include "geometry/VectorN.h"
#include "geometry/Vector2.h"
#include "geometry/Vector3.h"

#include "geometry/Circle.h"
#include "geometry/Rect.h"
#include "geometry/ShapeOverlap.h"

#include "maths/Common.h"
#include "maths/SquareMatrix.h"

#include "dataStorage/BinaryHeap.h"
#include "dataStorage/QuadTree.h"

#include "maths/Continuous.h"

#include "testing/VectorTests.h"

int main() {
	testing::vectors::all();

	chcl::VectorN<2> Vector1(5.f);

	std::cout << "Template vector2: [x: " << Vector1[0] << ", y: " << Vector1[1] << "]\n";

	chcl::Vector2<> Vector2_1(3.f), Vector2_2(5.f);

	std::cout << "Vector2: [x: " << Vector2_1.x << ", y: " << Vector2_1.y << "]\n";

	std::cout << "CHCL Vector2 print: "; chcl::printVector(Vector2_2); std::cout << '\n';

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

	chcl::Vector2<float> vec1, vec2(3), vec3(5, 1),
		vec4(vec2 + vec3), vec5(vec4.normalized()), vec6(vec2.normalized());

	std::cout << "Vector2 #1 (blank): "; printVector(vec1);
	std::cout << "Vector2 #2 (from 3): "; printVector(vec2);
	std::cout << "Vector2 #3 (from {5, 1}): "; printVector(vec3);
	std::cout << "Vector2 #2 + #3: "; printVector(vec2 + vec3);
	std::cout << "Vector2 #4 (from vec2 + vec3): "; printVector(vec4);
	std::cout << "Vector2 #5 (vec4 normalised): "; printVector(vec5);
	std::cout << "Vector2 #6 (vec2 normalised): "; printVector(vec6);

	std::cout << "Vector2 #5 as Matrix:\n"; chcl::printMatrix(vec5.toMatrix());

	float vals[] = { 0.482251f, -4.62f, 19, 42069, -729, 100.99f };
	//chcl::Matrix<0, 0> matrix1;
	chcl::Matrix<2, 3> matrix2;
	chcl::Matrix<4, 2> matrix3(3.f);
	chcl::Matrix<5, 4> matrix4(6.f);
	chcl::Matrix<3, 2> matrix5(vals);

	//std::cout << "\nMatrix #1 (blank):\n"; chcl::printMatrix(matrix1);
	std::cout << "\nMatrix #2 (2x3):\n"; chcl::printMatrix(matrix2);
	std::cout << "Matrix #3 (4x2, default 3.f):\n"; chcl::printMatrix(matrix3);
	std::cout << "Matrix #4 (5x4, default 6.f):\n"; chcl::printMatrix(matrix4);
	std::cout << "Matrix #5 (from float array):\n"; chcl::printMatrix(matrix5, 8);
	std::cout << "Matrix #4 * #3:\n"; chcl::printMatrix(matrix4 * matrix3);

	chcl::Mat4 transform = chcl::Mat4::Identity();
	transform *= chcl::Mat4::Translation(2, 3, 5);
	transform *= chcl::Mat4::Rotation2D(chcl::toRadians(35.f));
	transform *= chcl::Mat4::Scale(2, 1.5f, 0.7f);

	std::cout << "\nTransform matrix to scale by [2, 1.5, 0.7], rotate by 35 degrees and translate by [2, 3, 5]:\n";
	chcl::printMatrix(transform);

	std::cout << "\nMatrix as 6D Vector (same values as Matrix #5): ";
	chcl::printVector<6, float>(chcl::Matrix<6, 1>(vals));

	std::cout << "\nMatrices from initializer lists:\n";
	chcl::Matrix<3, 2> matrix6({
		 0.5f,   0.2f,
		 0.3f,   1.3f,
		-2.1f, 0.007f
	});
	std::cout << "Matrix6:\n"; chcl::printMatrix(matrix6);

	chcl::Matrix<4, 3> matrix7({
			     0.4f,   1.4f,    4.7f,
			    0.09f,  -7.5f,  11.92f,
			-109.775f,   60.f,   31.8f,
			    12.9f,  -47.f, -0.038f
		});
	std::cout << "Matrix7:\n";
	chcl::printMatrix(matrix7);

	std::cout << "Matrix7 * Matrix6:\n";
	chcl::printMatrix(matrix7 * matrix6);

	std::cout << "\nMatrix determinants:\n";
	chcl::SquareMatrix<2> detMatrix1({
			4, 6,
			3, 8
		});
	std::cout << "Matrix 1:\n";
	chcl::printMatrix(detMatrix1);
	std::cout << "Determinant: " << detMatrix1.determinant() << "\n\n";

	chcl::SquareMatrix<3> detMatrix2({
			6,  1,  1,
			4, -2,  5,
			2,  8,  7
		});
	std::cout << "Matrix 2:\n";
	chcl::printMatrix(detMatrix2);
	std::cout << "Determinant: " << detMatrix2.determinant() << "\n\n";

	chcl::Matrix identity5 = chcl::SquareMatrix<5>::Identity();
	std::cout << "5x5 Identity matrix:\n";
	chcl::printMatrix(identity5, 0);
	std::cout << '\n';

	chcl::Matrix rotation90 = chcl::Mat2::Rotation(chcl::toRadians(90.f)),
		rotation215 = chcl::Mat2::Rotation(chcl::toRadians(215.f));
	std::cout << "90 degree rotation matrix: \n";
	chcl::printMatrix(rotation90);
	std::cout << "215 degree rotation matrix:\n";
	chcl::printMatrix(rotation215);
	std::cout << '\n';

	chcl::Mat2 rot45 = chcl::Mat2::Rotation(chcl::toRadians(45.f));
	chcl::Vector2<> rotVec(1, 2);
	chcl::Vector2<> rotResult = rot45 * rotVec;

	std::cout << "Rotating vector "; chcl::printVector(rotVec); std::cout << " by 45 degrees: "; chcl::printVector(rotResult);

	chcl::Mat3 rot30_60 = chcl::Mat3::Rotation(chcl::toRadians(30.f), chcl::toRadians(60));
	chcl::Vector3<> rotVec3D(0, 3, 1);
	chcl::Vector3<> rotResult3D = rot30_60 * rotVec3D;

	std::cout << "Rotating vector "; chcl::printVector(rotVec3D); std::cout << " by 30 degrees pitch and 60 degrees yaw: "; chcl::printVector(rotResult3D);

	chcl::Rect rect1(3, 5, 13, 7);
	chcl::Vector2<> rectVec1(6, 2),	// Above
		rectVec2(29, 8),			// To the right
		rectVec3(12, 11);			// Inside

	std::cout << "Rect1 contains point 1? " << rect1.containsPoint(rectVec1) << '\n';
	std::cout << "Rect1 contains point 2? " << rect1.containsPoint(rectVec2) << '\n';
	std::cout << "Rect1 contains point 3? " << rect1.containsPoint(rectVec3) << '\n';

	chcl::Rect rect2(7, 6, 9, 5),	// TL contained
		rect3(4, 6, 11, 5),			// Completely contained
		rect4(-4, 1, 25, 18);		// Completely contains rect1

	std::cout << "Rect1 overlaps Rect2? " << chcl::checkOverlap(rect1, rect2) << '\n';
	std::cout << "Rect1 overlaps Rect3? " << chcl::checkOverlap(rect1, rect3) << '\n';
	std::cout << "Rect1 overlaps Rect4? " << chcl::checkOverlap(rect1, rect4) << '\n';

	chcl::QuadTree<std::string> qt(chcl::Rect(0, 0, 100, 100));

	qt.addElement("Test 1 at [10, 10]", { 10, 10 });
	qt.addElement("Test 2 at [15, 9]", { 15, 9 });
	qt.addElement("Test 3 at [70, 22]", { 70, 22 });
	qt.addElement("Test 4 at [10, 10]", { 10, 10 });

	std::cout << "\nConstraining 671 degrees to [0, 360): " << chcl::degreeSolver.clamp(671) << '\n';
	std::cout << "Smallest difference between 153 and 671 degrees: " << chcl::degreeSolver.diffMin(153, 671) << '\n';
	std::cout << "Minor average between 153 and 671 degrees: " << chcl::degreeSolver.avgMin(153, 671) << '\n';
	std::cout << "Smallest difference between 671 and 153 degrees: " << chcl::degreeSolver.diffMin(671, 153) << '\n';
	std::cout << "Minor average between 671 and 153 degrees: " << chcl::degreeSolver.avgMin(671, 153) << '\n';

	chcl::ContinuousSolver vectorSolver(chcl::Vector2<>(0.f), chcl::Vector2<>(10, 5));

	std::cout << "Constraining vector [33, 17] to between [0, 0] and [10, 5] on a continuous plane: "; chcl::printVector(vectorSolver.clamp({ 33.f, 17.f }));
	std::cout << "Distance between vectors [1, 2] and [9, 9]: "; chcl::printVector(vectorSolver.diffMin({ 1.f, 2.f }, { 9.f, 9.f }));

	chcl::BinaryHeap<int, [](const int &a, const int &b) { return a < b; }> binaryHeap;
	binaryHeap.add(10);
	binaryHeap.add(17);
	binaryHeap.add(9);
	binaryHeap.add(13);
	binaryHeap.add(2);
}