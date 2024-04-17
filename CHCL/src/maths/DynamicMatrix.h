#pragma once

#include <vector>

#include <maths/Matrix.h>
#include "geometry/Vector2.h"

namespace chcl
{
	/**
	 * @brief Class for dynamically sized matrices.
	 */
	class DynamicMatrix
	{
	public:
		DynamicMatrix();

		DynamicMatrix(unsigned int width, unsigned int height, float defaultVal = 0.0);

		DynamicMatrix(const DynamicMatrix &other);

		DynamicMatrix(DynamicMatrix &&other);

		template <unsigned int width, unsigned int height>
		DynamicMatrix(const Matrix<width, height> &matrix) :
			m_width(width), m_height(height),
			m_elements(matrix.values())
		{}

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }
		inline Vector2<unsigned int> getSize() const { return { m_width, m_height }; }

		float& at(unsigned int row, unsigned int col);
		const float& at(unsigned int row, unsigned int col) const;

		DynamicMatrix& operator =(const DynamicMatrix &other);
		DynamicMatrix& operator+=(const DynamicMatrix &other);
		DynamicMatrix& operator-=(const DynamicMatrix &other);
		DynamicMatrix& operator*=(const DynamicMatrix &other);

		friend DynamicMatrix operator+(DynamicMatrix lhs, const DynamicMatrix &rhs);
		friend DynamicMatrix operator-(DynamicMatrix lhs, const DynamicMatrix &rhs);
		friend DynamicMatrix operator*(const DynamicMatrix& lhs, const DynamicMatrix &rhs);

	private:
		unsigned int m_width, m_height;
		std::vector<float> m_elements;

		void resize(unsigned int newWidth, unsigned int newHeight);
		inline void resize(Vector2<unsigned int> newSize) { resize(newSize.x, newSize.y); }
	};
}