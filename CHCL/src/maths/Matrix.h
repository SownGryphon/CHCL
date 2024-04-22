#pragma once

#include <functional>

namespace chcl
{
	template <size_t rows, size_t cols, typename T, template <size_t, size_t, typename> typename Derived>
	class MatrixBase
	{
		using ValueType = T;
		using DerivedType = Derived<rows, cols, ValueType>;
	protected:
		ValueType m_values[rows * cols];

	public:
		MatrixBase() : m_values{} {}

		/**
		 * @brief Constructor for value-filled matrix
		 * @param defaultVal Value to fill matrix with
		 */
		MatrixBase(ValueType defaultVal)
		{
			std::fill_n(m_values, rows * cols, defaultVal);
		}

		/**
		 * @brief Constructor using T array
		 * @param values T array of values. Must be the same size as matrix
		 */
		explicit MatrixBase(const ValueType *values)
		{
			for (size_t i = rows * cols; i--;)
				m_values[i] = values[i];
		}
		
		/**
		 * @brief Constructor using initializer list
		 * @param values Initializer list of Ts
		 */
		MatrixBase(std::initializer_list<T> values)
		{
			for (size_t i = rows * cols; i--;)
				m_values[i] = values.begin()[i];
		}

		/**
		 * @brief Copy constructor
		 */
		MatrixBase(const MatrixBase& other)
			: MatrixBase(other.m_values)
		{}

		/**
		 * @brief Resizes a matrix to a new size by padding/cutting the bottom right corner
		 * @tparam newRows Number of rows in new matrix
		 * @tparam newrows Number of columns in new matrix
		 * @param mat Matrix to resize
		 * @return Resized matrix
		 */
		template <size_t newRows, size_t newCols>
		static Derived<newRows, newCols, ValueType> Resize(const DerivedType &mat)
		{
			MatrixBase<newRows, newCols, ValueType> result;
			for (size_t j = 0; j < std::min(rows, newRows); ++j)
			{
				for (size_t i = 0; i < std::min(cols, newCols); ++i)
				{
					result.at(j, i) = mat.at(j, i);
				}
			}
			return result;
		}

		ValueType* values() { return m_values; }
		const ValueType* values() const { return m_values; }

		const ValueType& at(size_t row, size_t col) const { return m_values[row * cols + col]; }
		ValueType& at(size_t row, size_t col) { return m_values[row * cols + col]; }

		Derived<1, 1, ValueType> getValueAsMatrix(size_t row, size_t col) const
		{
			return Derived<1, 1, ValueType>(at(row, col));
		}

		void getCol(size_t col, ValueType* out) const
		{
			for (size_t i = 0; i < rows; ++i)
			{
				out[i] = at(i, col);
			}
		}

		void getRow(size_t row, ValueType* out) const
		{
			for (size_t i = 0; i < cols; ++i)
			{
				out[i] = at(row, i);
			}
		}

		Derived<rows, 1, ValueType> getColAsMatrix(size_t col) const
		{
			Derived<rows, 1, ValueType> result;
			for (size_t i = 0; i < rows; ++i)
			{
				result.at(i, 0) = at(i, col);
			}
			return result;
		}

		Derived<1, cols, ValueType> getRowAsMatrix(size_t row) const
		{
			return Derived<1, cols, ValueType>(&at(row, 0));
		}

		/**
		 * @brief Transposes a matrix
		 * @return The transposed matrix
		 */
		Derived<cols, rows, ValueType> transpose() const
		{
			Derived<cols, rows, ValueType> result;
			for (size_t i = 0; i < rows; ++i)
			{
				for (size_t j = 0; j < cols; ++j)
				{
					result.at(j, i) = at(i, j);
				}
			}
		}

		/**
		 * @brief Bool cast
		 * Evaluates to false is all elements are zero
		 */
		explicit operator bool() const
		{
			if (rows == 0 || cols == 0)
				return false;

			for (size_t i = rows * cols; i--;)
			{
				if (m_values[i] != 0)
				{
					return true;
				}
			}

			return false;
		}

		friend DerivedType operator*(DerivedType mat, ValueType num)
		{
			return mat *= num;
		}

		friend DerivedType operator*(ValueType num, DerivedType mat)
		{
			return mat *= num;
		}

		friend DerivedType operator/(DerivedType mat, ValueType num)
		{
			return mat /= num;
		}

		friend DerivedType operator+(DerivedType lhs, const DerivedType &rhs)
		{
			return lhs += rhs;
		}

		friend DerivedType operator-(DerivedType lhs, const DerivedType &rhs)
		{
			return lhs -= rhs;
		}

		template <size_t otherCols>
		friend Derived<rows, otherCols, ValueType> operator*(const DerivedType &lhs, const Derived<cols, otherCols, ValueType> &rhs)
		{
			Derived<rows, otherCols, ValueType> result;
			for (size_t i = 0; i < rows; ++i)
			{
				for (size_t k = 0; k < cols; ++k)
				{
					for (size_t j = 0; j < otherCols; ++j)
					{
						result.at(i, j) += lhs.at(i, k) * rhs.at(k, j);
					}
				}
			}
			return result;
		}

		/**
		 * @brief Applies a function to every element
		 * @param func Function to apply to each element. Must take and return a T
		 */
		void perValue(std::function<ValueType(ValueType)> func)
		{
			for (size_t i = rows * cols; i--;)
			{
				m_values[i] = func(m_values[i]);
			}
		}

		// ===== Matrix type arithmetic =====

		DerivedType& operator =(std::initializer_list<ValueType> values)
		{
			for (size_t i = rows * cols; i--;)
				m_values[i] = values.begin()[i];
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator =(ValueType num)
		{
			std::fill_n(m_values, cols * rows, num);
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator*=(ValueType num)
		{
			perValue([num](ValueType val) { return val * num; });
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator/=(ValueType num)
		{
			perValue([num](ValueType val) { return val / num; });
			return *static_cast<DerivedType*>(this);
		}

		// ===== Matrix arithmetic =====

		DerivedType& operator =(const DerivedType &other)
		{
			std::memcpy(m_values, other.m_values, size_t(cols) * rows * sizeof(T));
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator+=(const DerivedType &other)
		{
			for (size_t i = rows * cols; i--;)
			{
				m_values[i] += other.m_values[i];
			}
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator-=(const DerivedType &other)
		{
			for (unsigned int i = rows * cols; i--;)
			{
				m_values[i] -= other.m_values[i];
			}
			return *static_cast<DerivedType*>(this);
		}

		DerivedType& operator*=(const Derived<cols, cols, T> &other)
		{
			*this = (*static_cast<DerivedType*>(this)) * other;
			return *static_cast<DerivedType*>(this);
		}

		friend bool operator==(const DerivedType &lhs, const DerivedType &rhs)
		{
			for (size_t i = cols * rows; i--;)
			{
				if (lhs.m_values[i] != rhs.m_values[i])
				{
					return false;
				}
			}

			return true;
		}

		friend bool operator!=(const DerivedType &lhs, const DerivedType &rhs)
		{
			return !(lhs == rhs);
		}
	};

	template <size_t rows, size_t cols, typename T = float>
	class Matrix : public MatrixBase<rows, cols, T, Matrix>
	{
	public:
		using MatrixBase<rows, cols, T, Matrix>::MatrixBase;
		using MatrixBase<rows, cols, T, Matrix>::operator=;
	};
}