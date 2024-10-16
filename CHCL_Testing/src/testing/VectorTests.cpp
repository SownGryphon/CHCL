#include "VectorTests.h"

#include <geometry/VectorN.h>
#include <geometry/Vector2.h>
#include <geometry/Vector3.h>

#include "../Asserts.h"

namespace testing
{
	namespace vectors
	{
		void all()
		{
			vectorN();
			vector2();
			vector3();

			conversion();
			operators();
		}

		void vectorN()
		{
			chcl::VectorN<4, int> vecInit;
			Asserts::Equal(vecInit[0], 0, "Default initializing vector failed.\n");

			chcl::VectorN<4, int> vec1, vec2(0);
			Asserts::Equal(vec1, vec2, "VectorN default constructor and single value constructor did not match.\n");

			float temp[] = { 2, 3.5f, 11.2f, -21.02f, -0.05f };
			chcl::VectorN<5, float> vec3(temp), vec4({ 2, 3.5f, 11.2f, -21.02f, -0.05f });
			Asserts::Equal(vec3, vec4, "VectorN array and intializer list constructors did not match.\n");

			Asserts::Equal(vec3.component(3), chcl::VectorN<5, float>({ 0, 0, 0, -21.02f, 0 }), "VectorN component does not work.\n");

			chcl::VectorN<4, int> vec5({ 1, 2, 3, 4 }), vec6({ 8, 7, 6, 5 });
			Asserts::Equal(chcl::VectorN<4, int>::Dot(vec5, vec6), 60, "Vector dot product incorrect.\n");

			Asserts::Equal(chcl::VectorN<4, float>(1).normalized(), chcl::VectorN<4, float>(0.5f), "VectorN normalization failed.\n");
		}


		void vector2()
		{

		}

		void vector3()
		{

		}

		void conversion()
		{

		}

		void operators()
		{

		}
	}
}