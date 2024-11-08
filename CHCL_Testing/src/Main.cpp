#include <algorithm>
#include <array>
#include <iostream>
#include <numbers>
#include <vector>

#include "chcl/Prints.h"

#include "chcl/geometry/VectorN.h"
#include "chcl/geometry/Vector2.h"
#include "chcl/geometry/Vector3.h"

#include "chcl/geometry/Quaternion.h"

#include "chcl/geometry/Circle.h"
#include "chcl/geometry/Rect.h"
#include "chcl/geometry/ShapeOverlap.h"

#include "chcl/maths/Common.h"
#include "chcl/maths/SquareMatrix.h"
#include "chcl/maths/Mat2.h"
#include "chcl/maths/Mat3.h"
#include "chcl/maths/Mat4.h"

#include "chcl/dataStorage/BinaryHeap.h"
#include "chcl/dataStorage/QuadTree.h"

#include "chcl/maths/Continuous.h"

#include "chcl/geometry/DynamicVector.h"
#include "chcl/maths/DynamicMatrix.h"

#include "chcl/dataStorage/JSON_Parser.h"
#include "chcl/dataStorage/JSON_Integration.h"

#include "tests/VectorTests.h"

class ConstructionTest
{
public:
	ConstructionTest()
	{
		std::cout << "Default constructed.\n";
	}

	ConstructionTest(int v) :
		data{ v }
	{
		std::cout << "Initialized with value " << data << ".\n";
	}

	ConstructionTest(const ConstructionTest &other) :
		data{ other.data }
	{
		std::cout << "Copy contructed (" << data << ").\n";
	}

	ConstructionTest(ConstructionTest &&other) noexcept :
		data{ other.data }
	{
		other.data = 0;
		std::cout << "Move constructed (" << data << ").\n";
	}

	~ConstructionTest()
	{
		std::cout << "Destroyed (" << data << ").\n";
	}

	ConstructionTest& operator=(const ConstructionTest &other)
	{
		data = other.data;
		std::cout << "Copy assigned (" << data << ").\n";
		return *this;
	}

	ConstructionTest& operator=(ConstructionTest &&other) noexcept
	{
		if (this != &other)
		{
			std::cout << "Move assigned (" << data << ").\n";
			data = other.data;
			other.data = 0;
		}
		else
			std::cout << "Move assigned to self.\n";
		return *this;
	}

private:
	int data = 0;
};

int main()
{
	testing::vectors::all();

	#if 0
	chcl::VectorN<2> Vector1(5.f);

	std::cout << "Template vector2: [x: " << Vector1[0] << ", y: " << Vector1[1] << "]\n";

	chcl::Vector2<> Vector2_1(3.f), Vector2_2(5.f);

	std::cout << "Vector2: [x: " << Vector2_1.x << ", y: " << Vector2_1.y << "]\n";

	std::cout << "CHCL Vector2 print: " << Vector2_2 << '\n';

	chcl::VectorN<5> Vector5_1, Vector5_2(4.2f), Vector5_3{ 0.1f, -3.7f, 17.73f, 2.957f, -175.9f };

	std::cout << "5D Vector #1: " << Vector5_1 << '\n';
	std::cout << "5D Vector #2: " << Vector5_2 << '\n';
	std::cout << "5D Vector #3: " << Vector5_3 << '\n';
	std::cout << "5D Vectors #2 + #3: " << (Vector5_2 + Vector5_3) << '\n';
	std::cout << "5D Vector #2 x 2: " << (Vector5_2 * 2) << '\n';
	std::cout << "5D Vector #3 / 3: " << (Vector5_3 / 3) << '\n';

	std::cout << "5D Vector #3 as Matrix:\n";
	chcl::printMatrix(Vector5_3.toMatrix());
	std::cout << '\n';

	chcl::Vector2<float> vec1, vec2(3), vec3(5, 1),
		vec4(vec2 + vec3), vec5(vec4.normalized()), vec6(vec2.normalized());

	std::cout << "Vector2 #1 (blank): " << vec1 << '\n';
	std::cout << "Vector2 #2 (from 3): " << vec2 << '\n';
	std::cout << "Vector2 #3 (from {5, 1}): " << vec3 << '\n';
	std::cout << "Vector2 #2 + #3: " << (vec2 + vec3) << '\n';
	std::cout << "Vector2 #4 (from vec2 + vec3): " << vec4 << '\n';
	std::cout << "Vector2 #5 (vec4 normalised): " << vec5 << '\n';
	std::cout << "Vector2 #6 (vec2 normalised): " << vec6 << '\n';

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
	std::cout << chcl::VectorN(chcl::Matrix<6, 1>(vals)) << '\n';

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

	std::cout << "Rotating vector " << rotVec << " by 45 degrees: " << rotResult << '\n';

	chcl::Mat3 rot30_60 = chcl::Mat3::Rotation(chcl::toRadians(30.f), chcl::toRadians(60));
	chcl::Vector3<> rotVec3D(0, 3, 1);
	chcl::Vector3<> rotResult3D = rot30_60 * rotVec3D;

	std::cout << "Rotating vector " << rotVec3D << " by 30 degrees pitch and 60 degrees yaw: " << rotResult3D << '\n';

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

	std::cout << "Constraining vector [33, 17] to between [0, 0] and [10, 5] on a continuous plane: " << vectorSolver.clamp({ 33.f, 17.f }) << '\n';
	std::cout << "Distance between vectors [1, 2] and [9, 9]: " << vectorSolver.diffMin({ 1.f, 2.f }, { 9.f, 9.f }) << '\n';

	chcl::BinaryHeap<int, [](const int &a, const int &b) { return a < b; }> binaryHeap;
	binaryHeap.add(10);
	binaryHeap.add(17);
	binaryHeap.add(9);
	binaryHeap.add(13);
	binaryHeap.add(2);

	chcl::DynamicMatrix dMat1(3, 3, std::vector{ 0.5f, 1.4f, -2.2f, 7.4f, 0.03f, -13.f, 5.f, 17.f, -0.113f });
	chcl::DynamicVector dVec1{ std::vector{ 3.7f, 1.1f, -5.2f } };

	chcl::DynamicVector dVecRes = dMat1 * dVec1;

	std::cout << dVecRes << '\n';

	chcl::Vector3<chcl::Vector2<float>> vecVec1;
	std::cout << "Vector of vectors: " << vecVec1 << '\n';

	chcl::SquareMatrix<2, chcl::Vector2<float>> vecMat;
	chcl::printMatrix(vecMat);
	#endif

	auto section = chcl::JSON_Parser::ReadFile<chcl::JSON_Object>("res/Test.json");
	std::string name = section.readElement<std::string>("name");
	int num = section.readElement<int>("num_test");
	auto numArr = section.readElement<std::vector<int>>("array_test");
	bool jsonBool = section.readElement<bool>("bool_test");
	auto subobject = section.readElement<chcl::JSON_Object>("object_test");
	auto subobjArr = section.readElement<std::vector<chcl::JSON_Object>>("obj_arr");

	chcl::JSON_Object writeSubObj;
	writeSubObj.writeElement("subObj1", subobject);
	writeSubObj.writeElement("subObj2", subobjArr[0]);
	writeSubObj.writeElement("subObj3", subobjArr[1]);
	writeSubObj.writeElement("subObjNum", 42069);

	chcl::JSON_Object writeObj;
	writeObj.writeElement("name", name);
	writeObj.writeElement("float", 3.141f);
	writeObj.writeElement("subObj", writeSubObj);

	chcl::JSON_Parser::SaveToFile("res/IntWrite.json", 5);
	chcl::JSON_Parser::SaveToFile("res/ArrWrite.json", numArr);
	chcl::JSON_Parser::SaveToFile("res/StrWrite.json", name);
	chcl::JSON_Parser::SaveToFile("res/FullWrite.json", writeObj);

	chcl::Vector3 jsonVec{ 0.5f, 0.2f, 22.7f };
	chcl::JSON_Parser::SaveToFile("res/VecWrite.json", jsonVec);
	auto jsonVecRead = chcl::JSON_Parser::ReadFile<chcl::DynamicVector<float>>("res/VecWrite.json");
	std::cout << "Vector read from JSON: " << jsonVecRead << '\n';

	chcl::Mat2 jsonMatWrite = chcl::Mat2::Rotation(chcl::toRadians(30));
	chcl::JSON_Parser::SaveToFile("res/MatWrite.json", jsonMatWrite);
	auto jsonMatRead = chcl::JSON_Parser::ReadFile<chcl::DynamicMatrix<float>>("res/MatWrite.json");
	std::cout << "Matrix read from JSON:\n";
	chcl::printMatrix(jsonMatRead);

	chcl::Quaternion rotQuat(chcl::Vector3<float>{ 1.f, 1.f, 1.f }, std::numbers::pi * 2.f / 3.f);
	chcl::Vector3<float> rotQuatVector(1.f, 2.f, 3.f);
	chcl::Vector3<float> rotQuatResult = rotQuat * (chcl::Quaternion)rotQuatVector * rotQuat.conj();
	std::cout << "Rotating vector using quaternions: " << rotQuatResult << '\n';
}