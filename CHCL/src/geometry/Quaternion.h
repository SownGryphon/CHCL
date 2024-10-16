#pragma once

#include "geometry/Vector3.h"

namespace chcl
{
	struct Quaternion
	{
		float re = 0.f, i = 0.f, j = 0.f, k = 0.f;

		Quaternion() = default;
		Quaternion(const Quaternion&) = default;
		Quaternion(Quaternion&&) = default;

		/**
		 * @brief Single value constructor
		 * 
		 * Constructs a quaternion with all components equal to the same value
		 * 
		 * @param val Value to set all components to
		 */
		Quaternion(float val);
		Quaternion(float re, float i, float j, float k);
		Quaternion(Vector3<float> vec);

		/**
		 * @brief Rotation quaternion constructor
		 * 
		 * Creates a quaternion that applies a rotation around a given axis
		 * 
		 * @param axis Axis to rotate around
		 * @param angle Angle to rotate by (following right-hand convention)
		 */
		Quaternion(Vector3<float> axis, float angle);

		float norm() const;
		float normSq() const;

		/**
		 * @brief Get the conjugate of the quaternion
		 * @return Quaternion conjugate
		 */
		Quaternion conj() const;

		Quaternion& operator=(const Quaternion&) = default;
		Quaternion& operator=(Quaternion&&) = default;

		Quaternion& operator+=(const Quaternion &other);
		Quaternion& operator-=(const Quaternion &other);
		Quaternion& operator*=(const Quaternion &other);

		Quaternion& operator*=(float scale);

		friend Quaternion operator+(const Quaternion &lhs, const Quaternion &rhs);
		friend Quaternion operator-(const Quaternion &lhs, const Quaternion &rhs);
		friend Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs);

		friend Quaternion operator*(const Quaternion &lhs, float scale);
		friend Quaternion operator*(float scale, const Quaternion &rhs);

		operator Vector3<float>() const;
	};
}