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
		DynamicMatrix(unsigned int rows, unsigned int cols, float defaultVal = 0.0);
		DynamicMatrix(unsigned int rows, unsigned int cols, const std::vector<float> &values);
		DynamicMatrix(const DynamicMatrix &other);
		DynamicMatrix(DynamicMatrix &&other);

		template <unsigned int rows, unsigned int cols>
		DynamicMatrix(const Matrix<rows, cols> &matrix) :
			m_rows(rows), m_cols(cols),
			m_elements(matrix.values())
		{}

		inline unsigned int rows() const { return m_rows; }
		inline unsigned int cols() const { return m_cols; }
		inline Vector2<unsigned int> size() const { return { m_rows, m_cols }; }

		float& at(unsigned int row, unsigned int col);
		const float& at(unsigned int row, unsigned int col) const;

		inline std::vector<float>& data() { return m_elements; }
		inline const std::vector<float>& data() const { return m_elements; }

		DynamicMatrix transpose() const;

		DynamicMatrix& operator =(const DynamicMatrix &other);
		DynamicMatrix& operator+=(const DynamicMatrix &other);
		DynamicMatrix& operator-=(const DynamicMatrix &other);
		DynamicMatrix& operator*=(const DynamicMatrix &other);

		DynamicMatrix& operator*=(float val);

		friend DynamicMatrix operator+(DynamicMatrix lhs, const DynamicMatrix &rhs);
		friend DynamicMatrix operator-(DynamicMatrix lhs, const DynamicMatrix &rhs);
		friend DynamicMatrix operator*(const DynamicMatrix& lhs, const DynamicMatrix &rhs);

		friend DynamicMatrix operator*(float val, DynamicMatrix mat);
		friend DynamicMatrix operator*(DynamicMatrix mat, float val);

	private:
		unsigned int m_rows, m_cols;
		std::vector<float> m_elements;

		void resize(unsigned int newRows, unsigned int newCols);
		inline void resize(Vector2<unsigned int> newSize) { resize(newSize.x, newSize.y); }
	};
}