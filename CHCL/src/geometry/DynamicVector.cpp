#include "DynamicVector.h"

#include <stdexcept>

chcl::DynamicVector::DynamicVector() {}

chcl::DynamicVector::DynamicVector(unsigned int size, float defaultVal)
{
	m_elements.resize(size);
	std::fill(m_elements.begin(), m_elements.end(), defaultVal);
}

chcl::DynamicVector::DynamicVector(const std::vector<float> &values) :
	m_elements{ values } {}

chcl::DynamicVector& chcl::DynamicVector::operator=(const DynamicVector &other)
{
	m_elements = other.m_elements;
	return *this;
}

chcl::DynamicVector& chcl::DynamicVector::operator+=(const DynamicVector &other)
{
	if (other.getSize() != getSize()) throw std::invalid_argument("Vector sizes invalid for operation.");

	for (unsigned int i = 0; i < m_elements.size(); ++i)
		(*this)[i] += other[i];

	return *this;
}

chcl::DynamicVector& chcl::DynamicVector::operator-=(const DynamicVector &other)
{
	if (other.getSize() != getSize()) throw std::invalid_argument("Vector sizes invalid for operation.");

	for (unsigned int i = 0; i < m_elements.size(); ++i)
		(*this)[i] -= other[i];

	return *this;
}

chcl::DynamicVector& chcl::DynamicVector::operator*=(const DynamicVector &other)
{
	if (other.getSize() != getSize()) throw std::invalid_argument("Vector sizes invalid for operation.");

	for (unsigned int i = 0; i < m_elements.size(); ++i)
		(*this)[i] *= other[i];

	return *this;
}

chcl::DynamicVector& chcl::DynamicVector::operator/=(const DynamicVector &other)
{
	if (other.getSize() != getSize()) throw std::invalid_argument("Vector sizes invalid for operation.");

	for (unsigned int i = 0; i < m_elements.size(); ++i)
		(*this)[i] /= other[i];

	return *this;
}

chcl::DynamicVector& chcl::DynamicVector::operator =(float val)
{
	for (unsigned int i = 0; i < m_elements.size(); ++i)
		(*this)[i] = val;

	return *this;
}

chcl::DynamicVector& chcl::DynamicVector::operator*=(float val)
{
	for (unsigned int i = 0; i < m_elements.size(); ++i)
		(*this)[i] *= val;

	return *this;
}

chcl::DynamicVector& chcl::DynamicVector::operator/=(float val)
{
	for (unsigned int i = 0; i < m_elements.size(); ++i)
		(*this)[i] /= val;

	return *this;
}

chcl::DynamicVector chcl::operator+(DynamicVector lhs, const DynamicVector &rhs)
{
	lhs += rhs;
	return lhs;
}

chcl::DynamicVector chcl::operator-(DynamicVector lhs, const DynamicVector &rhs)
{
	lhs -= rhs;
	return lhs;
}

chcl::DynamicVector chcl::operator*(DynamicVector lhs, const DynamicVector &rhs)
{
	lhs *= rhs;
	return lhs;
}

chcl::DynamicVector chcl::operator/(DynamicVector lhs, const DynamicVector &rhs)
{
	lhs /= rhs;
	return lhs;
}

chcl::DynamicVector chcl::operator*(DynamicVector lhs, float rhs)
{
	lhs *= rhs;
	return lhs;
}

chcl::DynamicVector chcl::operator/(DynamicVector lhs, float rhs)
{
	lhs /= rhs;
	return lhs;
}

chcl::DynamicVector chcl::operator*(float lhs, DynamicVector rhs)
{
	DynamicVector lhsVec{ rhs.getSize(), lhs };
	lhsVec *= rhs;
	return lhsVec;
}

chcl::DynamicVector chcl::operator/(float lhs, DynamicVector rhs)
{
	DynamicVector lhsVec{ rhs.getSize(), lhs };
	lhsVec /= rhs;
	return lhsVec;
}