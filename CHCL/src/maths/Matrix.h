#pragma once

#include <functional>

namespace chcl
{
	template <unsigned int rows, unsigned int cols, typename T, template <unsigned int, unsigned int, typename> typename Derived>
	class MatrixBase
	{
	protected:
		T m_values[rows * cols];

	public:
		/**
		 * @brief Constructor for value-filled matrix
		 * @param defaultVal Value to fill matrix with
		 */
		MatrixBase(T defaultVal = T(0))
		{
			std::fill(m_values, m_values + rows * cols, defaultVal);
		}

		/**
		 * @brief Constructor using T array
		 * @param values T array of values. Must be the same size as matrix
		 */
		explicit MatrixBase(const T *values)
		{
			std::memcpy(m_values, values, rows * cols * sizeof(T));
		}
		
		/**
		 * @brief Constructor using initializer list
		 * @param values Initializer list of Ts
		 */
		MatrixBase(std::initializer_list<T> values)
		{
			std::memcpy(m_values, values.begin(), values.size() * sizeof(T));
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
		template <unsigned int newRows, unsigned int newCols>
		static Derived<newRows, newCols, T> Resize(const Derived<rows, cols, T> &mat)
		{
			MatrixBase<newRows, newCols, T> result;
			for (unsigned int j = 0; j < std::min(rows, newRows); ++j)
			{
				for (unsigned int i = 0; i < std::min(cols, newCols); ++i)
				{
					result.at(j, i) = mat.at(j, i);
				}
			}
			return result;
		}

		T* values() { return m_values; }
		const T* values() const { return m_values; }

		const T& at(unsigned int row, unsigned int col) const { return m_values[size_t(row) * cols + col]; }
		T& at(unsigned int row, unsigned int col) { return m_values[size_t(row) * cols + col]; }

		Derived<1, 1, T> getValueAsMatrix(unsigned int row, unsigned int col) const
		{
			return Derived<1, 1, T>(at(row, col));
		}

		void getCol(unsigned int col, T* out) const
		{
			for (unsigned int i = 0; i < rows; ++i)
			{
				out[i] = at(i, col);
			}
		}

		void getRow(unsigned int row, T* out) const
		{
			for (unsigned int i = 0; i < cols; ++i)
			{
				out[i] = at(row, i);
			}
		}

		Derived<rows, 1, T> getColAsMatrix(unsigned int col) const
		{
			Derived<rows, 1, T> result;
			for (unsigned int i = 0; i < rows; ++i)
			{
				result.at(i, 0) = at(i, col);
			}
			return result;
		}

		Derived<1, cols, T> getRowAsMatrix(unsigned int row) const
		{
			return Derived<1, cols, T>(&at(row, 0));
		}

		/**
		 * @brief Transposes a matrix
		 * @return The transposed matrix
		 */
		Derived<rows, cols, T> transpose() const
		{
			Derived<cols, rows, T> result;
			for (int i = 0; i < rows; ++i)
			{
				for (int j = 0; j < cols; ++j)
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

			for (unsigned int i = rows * cols; i--;)
			{
				if (m_values[i] != 0)
				{
					return true;
				}
			}

			return false;
		}

		friend Derived<rows, cols, T> operator*(Derived<rows, cols, T> mat, T num)
		{
			return mat *= num;
		}

		friend Derived<rows, cols, T> operator*(T num, Derived<rows, cols, T> mat)
		{
			return mat *= num;
		}

		friend Derived<rows, cols, T> operator/(Derived<rows, cols, T> mat, T num)
		{
			return mat /= num;
		}

		friend Derived<rows, cols, T> operator+(Derived<rows, cols, T> lhs, const Derived<rows, cols, T> &rhs)
		{
			return lhs += rhs;
		}

		friend Derived<rows, cols, T> operator-(Derived<rows, cols, T> lhs, const Derived<rows, cols, T> &rhs)
		{
			return lhs -= rhs;
		}

		template <unsigned int otherCols>
		friend Derived<rows, otherCols, T> operator*(const Derived<rows, cols, T> &lhs, const Derived<cols, otherCols, T> &rhs)
		{
			Derived<rows, otherCols, T> result;
			for (unsigned int i = 0; i < rows; ++i)
			{
				for (unsigned int k = 0; k < cols; ++k)
				{
					for (unsigned int j = 0; j < otherCols; ++j)
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
		void perValue(std::function<T(T)> func)
		{
			for (unsigned int i = rows * cols; i--;)
			{
				m_values[i] = func(m_values[i]);
			}
		}

		// ===== Matrix type arithmetic =====

		Derived<rows, cols, T>& operator =(std::initializer_list<T> values)
		{
			std::memcpy(m_values, values.begin(), values.size() * sizeof(T));
			return *static_cast<Derived<rows, cols, T>*>(this);
		}

		Derived<rows, cols, T>& operator =(T num)
		{
			std::fill(m_values, m_values + size_t(cols) * rows, num);
			return *static_cast<Derived<rows, cols, T>*>(this);
		}

		Derived<rows, cols, T>& operator*=(T num)
		{
			perValue([num](T val) { return val * num; });
			return *static_cast<Derived<rows, cols, T>*>(this);
		}

		Derived<rows, cols, T>& operator/=(T num)
		{
			perValue([num](T val) { return val / num; });
			return *static_cast<Derived<rows, cols, T>*>(this);
		}

		// ===== Matrix arithmetic =====

		Derived<rows, cols, T>& operator =(const Derived<rows, cols, T> &other)
		{
			std::memcpy(m_values, other.m_values, size_t(cols) * rows * sizeof(T));
			return *static_cast<Derived<rows, cols, T>*>(this);
		}

		Derived<rows, cols, T>& operator+=(const Derived<rows, cols, T> &other)
		{
			for (unsigned int i = rows * cols; i--;)
			{
				m_values[i] += other.m_values[i];
			}
			return *static_cast<Derived<rows, cols, T>*>(this);
		}

		Derived<rows, cols, T>& operator-=(const Derived<rows, cols, T> &other)
		{
			for (unsigned int i = rows * cols; i--;)
			{
				m_values[i] -= other.m_values[i];
			}
			return *static_cast<Derived<rows, cols, T>*>(this);
		}

		Derived<rows, cols, T>& operator*=(const Derived<cols, cols, T> &other)
		{
			*this = (*static_cast<Derived<rows, cols, T>*>(this)) * other;
			return *static_cast<Derived<rows, cols, T>*>(this);
		}

		friend bool operator==(const Derived<rows, cols, T> &lhs, const Derived<rows, cols, T> &rhs)
		{
			for (unsigned int i = cols * rows; i--;)
			{
				if (lhs.m_values[i] != rhs.m_values[i])
				{
					return false;
				}
			}

			return true;
		}

		friend bool operator!=(const Derived<rows, cols, T> &lhs, const Derived<rows, cols, T> &rhs)
		{
			return !(lhs == rhs);
		}
	};

	template <unsigned int rows, unsigned int cols, typename T = float>
	class Matrix : public MatrixBase<rows, cols, T, Matrix>
	{
	public:
		using MatrixBase<rows, cols, T, Matrix>::MatrixBase;
		using MatrixBase<rows, cols, T, Matrix>::operator=;
	};
}