#pragma once

#include <vector>

#include "maths/DynamicMatrix.h"

namespace chcl
{
	class DynamicVector
	{
	public:
		DynamicVector();
		DynamicVector(unsigned int size, float defaultVal = 0.f);
		DynamicVector(const std::vector<float> &values);
		DynamicVector(const DynamicMatrix &mat);

		inline DynamicMatrix toMatrix() const { return DynamicMatrix(size(), 1, m_elements); }

		operator DynamicMatrix() const { return toMatrix(); }

		inline unsigned int size() const { return m_elements.size(); }

		inline float& operator[](unsigned int i) { return m_elements[i]; }
		inline const float& operator[](unsigned int i) const { return m_elements[i]; }
		
		inline std::vector<float>& data() { return m_elements; }
		inline const std::vector<float>& data() const { return m_elements; }

		DynamicVector& operator =(const DynamicVector &other);
		DynamicVector& operator+=(const DynamicVector &other);
		DynamicVector& operator-=(const DynamicVector &other);
		DynamicVector& operator*=(const DynamicVector &other);
		DynamicVector& operator/=(const DynamicVector &other);
		
		DynamicVector& operator =(float val);
		DynamicVector& operator*=(float val);
		DynamicVector& operator/=(float val);

		friend DynamicVector operator+(DynamicVector lhs, const DynamicVector &rhs);
		friend DynamicVector operator-(DynamicVector lhs, const DynamicVector &rhs);
		friend DynamicVector operator*(DynamicVector lhs, const DynamicVector &rhs);
		friend DynamicVector operator/(DynamicVector lhs, const DynamicVector &rhs);

		friend DynamicVector operator*(DynamicVector lhs, float rhs);
		friend DynamicVector operator/(DynamicVector lhs, float rhs);
		friend DynamicVector operator*(float lhs, DynamicVector rhs);
		friend DynamicVector operator/(float lhs, DynamicVector rhs);

		friend DynamicVector operator*(const DynamicMatrix &lhs, const DynamicVector &rhs);

	private:
		std::vector<float> m_elements;
	};
}