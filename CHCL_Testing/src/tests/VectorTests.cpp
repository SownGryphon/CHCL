#include "VectorTests.h"

#include <chcl/geometry/VectorN.h>
#include <chcl/geometry/Vector2.h>
#include <chcl/geometry/Vector3.h>

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
			Asserts::Equal(chcl::VectorN<4, int>()[0], 0, "Default initializing vector failed.\n");

			Asserts::Equal(chcl::VectorN<4, int>(), chcl::VectorN<4, int>(0), "VectorN default constructor and single value constructor did not match.\n");

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
			Asserts::Equal(chcl::Vector2<int>().x, 0, "Integer Vector2 initialization failed.");
			Asserts::Equal(chcl::Vector2<float>().x, 0.f, "Float Vector2 initialization failed.");
			Asserts::Equal(chcl::Vector2<int>(), chcl::Vector2<int>(0), "Integer Vector2 default and value constructors do not match.");
			Asserts::Equal(chcl::Vector2<float>(), chcl::Vector2<float>(0.f), "Float Vector2 default and value constructors do not match.");
		}

		void vector3()
		{
			Asserts::Equal(chcl::Vector3<int>().x, 0, "Integer Vector3 initialization failed.");
			Asserts::Equal(chcl::Vector3<float>().x, 0.f, "Float Vector3 initialization failed.");
			Asserts::Equal(chcl::Vector3<int>(), chcl::Vector3<int>(0), "Integer Vector3 default and value constructors do not match.");
			Asserts::Equal(chcl::Vector3<float>(), chcl::Vector3<float>(0.f), "Float Vector3 default and value constructors do not match.");
		}

		void conversion()
		{

		}

		void operators()
		{

		}
	}
}