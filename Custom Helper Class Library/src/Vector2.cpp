#include "Vector2.h"

#include <cmath>

using namespace chcl;

Vector2::Vector2() :
	x{ 0.f }, y{ 0.f } {}

Vector2::Vector2(float num) :
	x{ num }, y{ num } {}

Vector2::Vector2(float x, float y) :
	x{ x }, y{ y } {}

Vector2 Vector2::xVector() const
{
	return Vector2(x, 0.f);
}

Vector2 Vector2::yVector() const
{
	return Vector2(0.f, y);
}

Matrix Vector2::asColMatrix() const
{
	Matrix result{ 1, 2 };
	result.getValue(0, 0) = x;
	result.getValue(0, 1) = y;

	return result;
}

float Vector2::magsq() const
{
	return x * x + y * y;
}

float Vector2::mag() const
{
	return std::sqrtf(magsq());
}

Vector2 chcl::operator+(Vector2 lhs, const Vector2& rhs)
{
	lhs += rhs;

	return lhs;
}

Vector2 chcl::operator-(Vector2 lhs, const Vector2& rhs)
{
	lhs -= rhs;

	return lhs;
}

Vector2 chcl::operator*(Vector2 lhs, const Vector2& rhs)
{
	lhs *= rhs;

	return lhs;
}

Vector2 chcl::operator/(Vector2 lhs, const Vector2& rhs)
{
	lhs /= rhs;

	return lhs;
}

Vector2 chcl::operator+(Vector2 vec, float val)
{
	vec.x += val;
	vec.y += val;

	return vec;
}

Vector2 chcl::operator-(Vector2 vec, float val)
{
	vec.x -= val;
	vec.y -= val;

	return vec;
}

Vector2 chcl::operator*(Vector2 vec, float val)
{
	vec.x *= val;
	vec.y *= val;

	return vec;
}

Vector2 chcl::operator/(Vector2 vec, float val)
{
	vec.x /= val;
	vec.y /= val;

	return vec;
}

Vector2 chcl::operator+(float val, Vector2 vec)
{
	vec.x += val;
	vec.y += val;

	return vec;
}

Vector2 chcl::operator-(float val, Vector2 vec)
{
	vec.x = val - vec.x;
	vec.y = val - vec.y;

	return vec;
}

Vector2 chcl::operator*(float val, Vector2 vec)
{
	vec.x *= val;
	vec.y *= val;

	return vec;
}

Vector2 chcl::operator/(float val, Vector2 vec)
{
	vec.x = val / vec.x;
	vec.y = val / vec.y;

	return vec;
}

Vector2& Vector2::operator =(const Vector2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	x /= other.x;
	y /= other.y;

	return *this;
}

Vector2 Vector2::normalised() const
{
	return *this / mag();
}

float Vector2::dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

bool Vector2::operator==(const Vector2& other) const
{
	return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}