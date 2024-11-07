#include "Quaternion.h"

chcl::Quaternion::Quaternion(float val) :
	re(val), i(val), j(val), k(val)
{}

chcl::Quaternion::Quaternion(float re, float i, float j, float k) :
	re(re), i(i), j(j), k(k)
{}

chcl::Quaternion::Quaternion(Vector3<float> vec) :
	re(0.f), i(vec.x), j(vec.y), k(vec.z)
{}

chcl::Quaternion::Quaternion(Vector3<float> axis, float angle)
{
	*this = Quaternion(axis.normalized()) * std::sinf(angle / 2.f);
	re = std::cosf(angle / 2.f);
}

float chcl::Quaternion::norm() const
{
	return std::sqrtf(normSq());
}

float chcl::Quaternion::normSq() const
{
	return re * re + i * i + j * j + k * k;
}

chcl::Quaternion chcl::Quaternion::conj() const
{
	return Quaternion(re, -i, -j, -k);
}

chcl::Quaternion& chcl::Quaternion::operator+=(const Quaternion &other)
{
	re += other.re;
	i += other.i;
	j += other.j;
	k += other.k;

	return *this;
}

chcl::Quaternion& chcl::Quaternion::operator-=(const Quaternion &other)
{
	re -= other.re;
	i -= other.i;
	j -= other.j;
	k -= other.k;

	return *this;
}

chcl::Quaternion& chcl::Quaternion::operator*=(const Quaternion &other)
{
	Quaternion temp;
	temp.re = re * other.re - i * other.i - j * other.j - k * other.k;
	temp.i = re * other.i + i * other.re + j * other.k - k * other.j;
	temp.j = re * other.j - i * other.k + j * other.re + k * other.i;
	temp.k = re * other.k + i * other.j - j * other.i + k * other.re;
	*this = temp;

	return *this;
}

chcl::Quaternion& chcl::Quaternion::operator*=(float scale)
{
	re *= scale;
	i *= scale;
	j *= scale;
	k *= scale;

	return *this;
}

chcl::Quaternion chcl::operator+(const Quaternion &lhs, const Quaternion &rhs)
{
	Quaternion res{ lhs };
	res += rhs;
	return res;
}

chcl::Quaternion chcl::operator-(const Quaternion &lhs, const Quaternion &rhs)
{
	Quaternion res{ lhs };
	res -= rhs;
	return res;
}

chcl::Quaternion chcl::operator*(const Quaternion &lhs, const Quaternion &rhs)
{
	Quaternion res{ lhs };
	res *= rhs;
	return res;
}

chcl::Quaternion chcl::operator*(const Quaternion &lhs, float scale)
{
	Quaternion res{ lhs };
	res *= scale;
	return res;
}

chcl::Quaternion chcl::operator*(float scale, const Quaternion &rhs)
{
	Quaternion res{ rhs };
	res *= scale;
	return res;
}

chcl::Quaternion::operator chcl::Vector3<float>() const
{
	return Vector3<float>(i, j, k);
}