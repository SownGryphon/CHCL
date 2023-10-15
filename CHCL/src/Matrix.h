#pragma once

#include <functional>

namespace chcl
{
	struct Matrix
	{
		unsigned int m_cols,
			m_rows;

		float* m_values;
	public:
		Matrix();
		Matrix(unsigned int cols, unsigned int rows, float defaultVal = 0.f);
		Matrix(unsigned int cols, unsigned int rows, const float* values);
		Matrix(unsigned int cols, unsigned int rows, std::initializer_list<float> values);
		Matrix(const Matrix& other);
		~Matrix();

		static Matrix Identity(unsigned int size);
		static Matrix Rotation2D(float angle);
		static Matrix Resize(const Matrix &mat, unsigned int width, unsigned int height);

		inline unsigned int getCols() const { return m_cols; }
		inline unsigned int getRows() const { return m_rows; }

		inline float* values() { return m_values; }
		inline const float* values() const { return m_values; }

		const float& at(unsigned int col, unsigned int row) const;
		float& at(unsigned int col, unsigned int row);

		Matrix getValueAsMatrix(unsigned int col, unsigned int row) const;

		void getCol(unsigned int col, float* out) const;
		void getRow(unsigned int row, float* out) const;

		Matrix getColAsMatrix(unsigned int col) const;
		Matrix getRowAsMatrix(unsigned int row) const;

		float determinant() const;

		explicit operator bool() const;

		friend Matrix operator*(const Matrix &matrix, float val);
		friend Matrix operator/(const Matrix &matrix, float val);
		friend Matrix operator*(float val, const Matrix &matrix);

		friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);
		friend Matrix operator-(const Matrix &lhs, const Matrix &rhs);
		friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);

		void perValue(std::function<float(float)>);

		Matrix& operator =(std::initializer_list<float> values);

		Matrix& operator =(float val);
		Matrix& operator*=(float val);
		Matrix& operator/=(float val);

		Matrix& operator =(const Matrix &other);
		Matrix& operator+=(const Matrix &other);
		Matrix& operator-=(const Matrix &other);
		Matrix& operator*=(const Matrix &other);

		bool operator==(const Matrix &other) const;
		bool operator!=(const Matrix &other) const;
	};
}