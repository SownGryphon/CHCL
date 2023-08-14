#pragma once

#include <functional>

namespace chcl
{
	struct Matrix
	{
	public:
		Matrix();
		Matrix(unsigned int cols, unsigned int rows, float defaultVal = 0.f);
		Matrix(unsigned int cols, unsigned int rows, float* values);
		Matrix(unsigned int cols, unsigned int rows, std::initializer_list<float> values);
		Matrix(const Matrix& other);
		~Matrix();

		inline unsigned int getCols() const { return m_cols; }
		inline unsigned int getRows() const { return m_rows; }

		inline float* const getValues() const { return m_values; }

		float at(unsigned int col, unsigned int row) const;
		float& at(unsigned int col, unsigned int row);	// Non-const variant

		Matrix getValueAsMatrix(unsigned int col, unsigned int row) const;

		void getCol(unsigned int col, float* out) const;
		void getRow(unsigned int row, float* out) const;

		Matrix getColAsMatrix(unsigned int col) const;
		Matrix getRowAsMatrix(unsigned int row) const;

		float determinant() const;

		operator bool() const;

		friend Matrix operator+(Matrix matrix, float val);
		friend Matrix operator-(Matrix matrix, float val);
		friend Matrix operator*(Matrix matrix, float val);
		friend Matrix operator/(Matrix matrix, float val);

		friend Matrix operator+(float val, Matrix matrix);
		friend Matrix operator-(float val, Matrix matrix);
		friend Matrix operator*(float val, Matrix matrix);
		friend Matrix operator/(float val, Matrix matrix);

		friend Matrix operator+(Matrix lhs, const Matrix& rhs);
		friend Matrix operator-(Matrix lhs, const Matrix& rhs);
		friend Matrix operator*(Matrix lhs, const Matrix& rhs);

		void perValue(std::function<float(float)>);

		Matrix& operator =(std::initializer_list<float> values);

		Matrix& operator =(float val);
		Matrix& operator+=(float val);
		Matrix& operator-=(float val);
		Matrix& operator*=(float val);
		Matrix& operator/=(float val);

		Matrix& operator =(const Matrix& other);
		Matrix& operator+=(const Matrix& other);
		Matrix& operator-=(const Matrix& other);
		Matrix& operator*=(const Matrix& other);

		bool operator==(const Matrix& other) const;
		bool operator!=(const Matrix& other) const;
	private:
		unsigned int m_cols,
			m_rows;

		float* m_values;
	};
}