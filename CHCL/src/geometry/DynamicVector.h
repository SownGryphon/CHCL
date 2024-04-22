#pragma once

#include <ostream>
#include <vector>

#include "maths/DynamicMatrix.h"

namespace chcl
{
	/**
	 * @brief Vector with a dynamic size
	 * @tparam T Vector component type
	 */
	template <typename T>
	class DynamicVector
	{
	public:
		using ValueType = T;

		DynamicVector() = default;

		DynamicVector(size_t size, ValueType defaultVal)
		{
			resize(size, defaultVal);
		}

		DynamicVector(const std::vector<ValueType> &values)
		{
			resize(values.size(), values.data());
		}

		DynamicVector(const DynamicMatrix<ValueType> &mat)
		{
			if (mat.cols() != 1) std::runtime_error("");

			resize(mat.rows(), mat.data());
		}

		DynamicVector(const DynamicVector &other)
		{
			resize(other.size(), other.data());
		}

		DynamicVector(DynamicVector &&other) = default;

		~DynamicVector()
		{
			clear();
		}

		inline DynamicMatrix<ValueType> toMatrix() const { return DynamicMatrix<ValueType>(size(), 1, m_elements); }

		operator DynamicMatrix<ValueType>() const { return toMatrix(); }

		inline size_t size() const { return m_size; }

		inline ValueType& operator[](size_t i) { return m_elements[i]; }
		inline const ValueType& operator[](size_t i) const { return m_elements[i]; }
		
		inline ValueType* data() { return m_elements; }
		inline const ValueType* data() const { return m_elements; }

		DynamicVector& operator =(const DynamicVector &other)
		{
			if (other.size() != m_size) resize(other.size(), other.data());
			else
				for (unsigned int i = 0; i < m_size; ++i)
					m_elements[i] = other[i];

			return *this;
		}
		DynamicVector& operator =(DynamicVector &&other) = default;

		DynamicVector& operator+=(const DynamicVector &other)
		{
			for (size_t i = 0; i < m_size; ++i)
				m_elements[i] += other[i];
			return *this;
		}

		DynamicVector& operator-=(const DynamicVector &other)
		{
			for (size_t i = 0; i < m_size; ++i)
				m_elements[i] -= other[i];
			return *this;
		}

		DynamicVector& operator*=(const DynamicVector &other)
		{
			for (size_t i = 0; i < m_size; ++i)
				m_elements[i] *= other[i];
			return *this;
		}

		DynamicVector& operator/=(const DynamicVector &other)
		{
			for (size_t i = 0; i < m_size; ++i)
				m_elements[i] /= other[i];
			return *this;
		}
		
		DynamicVector& operator =(ValueType val)
		{
			for (unsigned int i = 0; i < m_size; ++i)
				(*this)[i] = val;

			return *this;
		}

		DynamicVector& operator+=(ValueType val)
		{
			for (unsigned int i = 0; i < m_size; ++i)
				(*this)[i] += val;

			return *this;
		}

		DynamicVector& operator-=(ValueType val)
		{
			for (unsigned int i = 0; i < m_size; ++i)
				(*this)[i] -= val;

			return *this;
		}

		DynamicVector& operator*=(ValueType val)
		{
			for (unsigned int i = 0; i < m_size; ++i)
				(*this)[i] *= val;

			return *this;
		}

		DynamicVector& operator/=(ValueType val)
		{
			for (unsigned int i = 0; i < m_size; ++i)
				(*this)[i] /= val;

			return *this;
		}

		friend DynamicVector operator+(DynamicVector lhs, const DynamicVector &rhs)
		{
			lhs += rhs;
			return lhs;
		}

		friend DynamicVector operator-(DynamicVector lhs, const DynamicVector &rhs)
		{
			lhs += rhs;
			return lhs;
		}

		friend DynamicVector operator*(DynamicVector lhs, const DynamicVector &rhs)
		{
			lhs += rhs;
			return lhs;
		}

		friend DynamicVector operator/(DynamicVector lhs, const DynamicVector &rhs)
		{
			lhs += rhs;
			return lhs;
		}

		friend DynamicVector operator*(DynamicVector lhs, ValueType rhs)
		{
			lhs *= rhs;
			return lhs;
		}

		friend DynamicVector operator/(DynamicVector lhs, ValueType rhs)
		{
			lhs /= rhs;
			return lhs;
		}

		friend DynamicVector operator*(ValueType lhs, DynamicVector rhs)
		{
			rhs *= lhs;
			return lhs;
		}

		friend DynamicVector operator/(ValueType lhs, DynamicVector rhs)
		{
			DynamicVector lhsVec{ rhs.size(), lhs };
			lhsVec /= rhs;
			return lhsVec;
		}

		friend DynamicVector operator*(const DynamicMatrix<ValueType> &lhs, const DynamicVector &rhs)
		{
			return lhs * DynamicMatrix<ValueType>(rhs);
		}

		friend std::ostream& operator<<(std::ostream &stream, const DynamicVector &vec)
		{
			stream << '[';
			for (size_t i = 0; i < vec.size(); ++i)
			{
				if (i)
					stream << ", ";
				stream << vec[i];
			}
			stream << ']';
			return stream;
		}

	private:
		size_t m_size = 0;
		ValueType *m_elements = nullptr;

		void clear()
		{
			for (size_t i = 0; i < m_size; ++i)
				m_elements[i].~ValueType();
			if (m_elements)
				::operator delete(m_elements, m_size * sizeof(ValueType));
			m_size = 0;
			m_elements = nullptr;
		}

		void resize(size_t newSize, const ValueType *newValues = nullptr)
		{
			ValueType *newBlock = (ValueType*)::operator new(newSize * sizeof(ValueType));

			for (size_t i = 0; i < newSize; ++i)
				if (newValues)
					new (&newBlock[i]) ValueType(newValues[i]);
				else
					new (&newBlock[i]) ValueType();

			clear();

			m_size = newSize;
			m_elements = newBlock;
		}

		void resize(size_t newSize, const ValueType newValue)
		{
			ValueType *newBlock = (ValueType*)::operator new(newSize * sizeof(ValueType));

			for (size_t i = 0; i < newSize; ++i)
				new (&newBlock[i]) ValueType(newValue);

			clear();

			m_size = newSize;
			m_elements = newBlock;
		}
	};
}