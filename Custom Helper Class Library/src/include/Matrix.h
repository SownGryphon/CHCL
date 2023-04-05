/**	@file Matrix.h
*	@brief Contains the declarations for the %Matrix class.
*/

#pragma once

#include <functional>

namespace chcl
{
	/**	@brief A matrix class that supports basic arithmetic operations.
	* 
	*	These matrices support basic arithmetic operators which can be used with floats and other matrices.
	*/
	struct Matrix
	{
	private:
		unsigned int m_cols,	/**< @brief Width of matrix. */
			m_rows;				/**< @brief Height of matrix. */
		
	public:
		/** @brief %Matrix values.
		* 
		*	The matrix elements, stored left-to-right, top-to-bottom.
		*/
		float* values;

		/** @name Constructors and Destructors */
		/**@{*/
		/** @brief Default construtor.
		* 
		*	Creates a 0 by 0 matrix with no values.
		*/
		Matrix();

		/** @brief Creates matrix of specific size.
		* 
		*	Creates a matrix of the given size, optionally filled with the specified value.
		*
		*	@param cols,rows The size of the matrix.
		*	@param defaultVal (optional) The value to which initialise all values of the matrix to.
		*/
		Matrix(unsigned int cols, unsigned int rows, float defaultVal = 0.f);

		/**	@brief Creates matrix from given values.
		* 
		*	Creates a matrix of the given size and fills it with the provided values.
		* 
		*	@param cols,rows The size of the matrix.
		*	@param values A float array containing the values to fill the matrix with.
		* 
		*	@remark Values array must be large enough to fil the entire matrix.
		*/
		Matrix(unsigned int cols, unsigned int rows, float* values);

		/** @brief Copy constructor.
		* 
		*	Creates a matrix with the same size as the given matrix and copies the given matrix's values.
		*
		*	@param other %Matrix to be copied.
		*/
		Matrix(const Matrix& other);

		/** @brief Deletes values array.
		*/
		~Matrix();
		/**@}*/

		/** @name Member Access Functions */
		/**@{*/
		/**	@brief Returns the number of columns.
		* 
		*	@returns Number of columns in the `this` matrix.
		*/
		unsigned int getCols() const;
		/**	@brief Returns the number of rows.
		* 
		*	@returns Number of rows in the `this` matrix.
		*/
		unsigned int getRows() const;

		/** @brief Returns the value in the given position.
		* 
		*	@param col,row The position of the desired value.
		* 
		*	@returns The value in the given position.
		* 
		*	@remark This is the const variant of this function.
		* 
		*	@throws out_of_bounds If trying to access an index outside the Matrux.
		*/
		float getValue(unsigned int col, unsigned int row) const;
		/** @brief Returns a reference to the value at the given position.
		* 
		*	@param col,row The position of the desired value.
		* 
		*	@returns A reference to the value in the given position.
		* 
		*	@remark This is the non-const variant of this function.
		* 
		*	@throws out_of_bounds If trying to access an index outside the `this` matrix.
		*/
		float& getValue(unsigned int col, unsigned int row);

		/**	@brief Returns the value as a matrix.
		* 
		*	Returns the value in the given position as a 1x1 matrix.
		* 
		*	@param col,row The position of the desired value.
		* 
		*	@returns A 1x1 matrix containing the desired value.
		* 
		*	@throws out_of_bound If trying to access an index outside the `this` matrix.
		*/
		Matrix getValueAsMatrix(unsigned int col, unsigned int row) const;

		/**	@brief Returns the given column.
		* 
		*	Returns the given column using the output parameter `out`.
		* 
		*	@param col Column to return.
		*	@param out A float array used as an output parameter.
		* 
		*	@remark Output variable must be passed in as an array of the correct size.
		* 
		*	@throws out_of_range If trying to access a column outside the `this` matrix.
		*/
		void getCol(unsigned int col, float* out) const;
		/**	@brief Returns the given row.
		* 
		*	Returns the given row using the output parameter `out`.
		*
		*	@param row Row to return.
		*	@param out A float array used as an output parameter.
		* 
		*	@remark Output variable must be passed in as an array of the correct size.
		* 
		*	@throws out_of_range If attempting to access a row outside the `this` matrix.
		*/
		void getRow(unsigned int row, float* out) const;

		/**	@brief Get a column as a matrix.
		* 
		*	Returns the given column as a column matrix.
		* 
		*	@param col Column to be returned.
		* 
		*	@returns A column matrix containing the given column.
		* 
		*	@throws out_of_bounds If trying to acccess a column outside the `this` matrix.
		*/
		Matrix getColAsMatrix(unsigned int col) const;
		/**	@brief Get a row as a matrix.
		* 
		*	Returns the given row as a row matrix.
		*
		*	@param row Row to be returned.
		*
		*	@returns A row matrix containing the given row.
		*
		*	@throws out_of_bound If trying to access a row outside the `this` matrix.
		*/
		Matrix getRowAsMatrix(unsigned int row) const;
		/**@}*/

		/**	Calculates the determinant of the matrix.
		* 
		*	@throws logic_error If the `this` matrix is not a square matrix.
		*/
		float determinant() const;

		/**	@brief Bool Cast.
		* 
		*	Allows for implicit or explicit conversion to a bool. Returns `false` if all values are 0, returns `true` otherwise. Also returns `false` if used on a zero matrix.
		*/
		operator bool() const;

		/** @name Arithmetic Operators */
		/**@{*/
		/**	@brief Float addition operator.
		* 
		*	Adds the given value to all elements of the matrix.
		* 
		*	@param matrix The matrix to add to.
		*	@param val Number to add to all matrix elements.
		*
		*	@returns The result of the addition.
		*/
		friend Matrix operator+(Matrix matrix, float val);
		/**	@brief Float subtraction operator.
		* 
		*	Subtracts the given value from all elements of the matrix.
		*
		*	@param matrix The matrix to subtract from.
		*	@param val Number to subtract from all matrix elements.
		*
		*	@returns The result of the subtraction.
		*/
		friend Matrix operator-(Matrix matrix, float val);
		/**	@brief Float multiplication operator.
		* 
		*	Multiplies all elements of the matrix by the given value.
		*
		*	@param matrix The matrix to multiply.
		*	@param val Number to multiply all matrix elements by.
		*
		*	@returns The result of the addition.
		*/
		friend Matrix operator*(Matrix matrix, float val);
		/**	@brief Float division operator.
		* 
		*	Divides all elements of the matrix by the given value.
		*
		*	@param matrix The matrix to divide.
		*	@param val Number to divide all matrix elements by.
		*
		*	@returns The result of the division.
		*/
		friend Matrix operator/(Matrix matrix, float val);

		/**	@brief Float addition operator.
		* 
		*	Adds the given value to all elements of the matrix.
		*
		*	@param val Number to add to all matrix elements.
		*	@param matrix The matrix to add to.
		*
		*	@returns The result of the addition.
		*/
		friend Matrix operator+(float val, Matrix matrix);
		/**	@brief Float subtraction operator.
		* 
		*	Returns a matrix containing the difference between `val` and the values of `matrix`.
		*
		*	@param val Number to subtract from.
		*	@param matrix The matrix to subtract from `val`.
		*
		*	@returns The result of the subtraction.
		*/
		friend Matrix operator-(float val, Matrix matrix);
		/**	@brief Float multiplication operator.
		* 
		*	Multiplies all elements of the matrix by the given value.
		*
		*	@param val Number to multiply all matrix elements by.
		*	@param matrix The matrix to multiply.
		*
		*	@returns The result of the addition.
		*/
		friend Matrix operator*(float val, Matrix matrix);
		/**	@brief Float division operator.
		* 
		*	Returns a matrix containing the quotient of `val` and the values of `matrix`.
		*
		*	@param val Number to divide.
		*	@param matrix The matrix to divide `val` by.
		*
		*	@returns The result of the division.
		*/
		friend Matrix operator/(float val, Matrix matrix);

		/**	@brief %Matrix addition operator.
		* 
		*	Adds the values of the two matrices and returns the result.
		*
		*	@param lhs,rhs The matrices to add.
		*
		*	@returns The result of the addition.
		* 
		*	@throws invalid_argument If the sizes of the two matrices do not match.
		*/
		friend Matrix operator+(Matrix lhs, const Matrix& rhs);
		/**	@brief %Matrix subtraction operator.
		* 
		*	Subtracts the values of the `rhs` matrix from the values of the `lhs` matrix.
		*
		*	@param lhs The matrix that will be subtracted from.
		*	@param rhs The matrix to be subtracted from the other matrix.
		*
		*	@returns The result of the subtraction.
		*
		*	@throws invalid_argument If the sizes of the two matrices do not match.
		*/
		friend Matrix operator-(Matrix lhs, const Matrix& rhs);

		/** @brief %Matrix multiplication operator.
		* 
		*	Executes matrix multiplication between given matrices.
		*
		*	@param lhs,rhs matrices to multiply.
		*
		*	@returns The result of the multiplication.
		* 
		*	@throws invalid_argument Throws this exception if the number of columns of the `lhs` matrix does not match the number of rows of the `rhs` matrix.
		*/
		friend Matrix operator*(Matrix lhs, const Matrix& rhs);
		/**@}*/

		/** @brief Per-value operation.
		* 
		*	Executes the supplied operation on each element of the matrix.
		* 
		*	@param func A `std::function` object to execute on each element of the matrix.
		*	Must be in the form `float func(float val)`, which takes in the current value of the element, and returns the new value.
		*/
		void perValue(std::function<float(float)>);

		/** @name Assignment Operators */
		/**@{*/
		/**	@brief Float assignment operator.
		* 
		*	Sets all matrix elements to `val`.
		*
		*	@param val The value to set all matrix elements to.
		*
		*	@returns A reference to itself after the assignment was complete.
		*/
		Matrix& operator =(float val);
		/**	@brief Float addition assignment operator.
		* 
		*	Adds `val` to all matrix elements.
		*
		*	@param val The value to add to all matrix elements.
		*
		*	@returns A reference to itself after the assignment was complete.
		*/
		Matrix& operator+=(float val);
		/**	@brief Float subtraction assignment operator.
		* 
		*	Subtracts `val` from all matrix elements.
		*
		*	@param val The value to subtract from all matrix elements.
		*
		*	@returns A reference to itself after the assignment was complete.
		*/
		Matrix& operator-=(float val);
		/**	@brief Float multiplication assignment operator.
		* 
		*	Multilpies all matrix elements by `val`.
		*
		*	@param val The value to multiply all matrix elements by.
		*
		*	@returns A reference to itself after the assignment was complete.
		*/
		Matrix& operator*=(float val);
		/**	@brief Float division assignment operator.
		* 
		*	Divides all matrix elements by `val`.
		*
		*	@param val The value to divide all matrix elements by.
		*
		*	@returns A reference to itself after the assignment was complete.
		*/
		Matrix& operator/=(float val);

		/**	@brief %Matrix assignment operator.
		* 
		*	Sets all values of the `this` matrix to the values of the `other` matrix. Resizes the `this` matrix if necessary.
		* 
		*	@param other The matrix to assign to.
		* 
		*	@returns A reference to itself after the assignment was complete.
		*/
		Matrix& operator =(const Matrix& other);
		/**	@brief %Matrix addition assignment operator.
		* 
		*	Adds the `other` matrix to the `this` matrix on a per-value basis.
		*
		*	@param other The matrix to add.
		*
		*	@returns A reference to itself after the assignment was complete.
		* 
		*	@throws invalid_argument If the sizes of the matrices do not match.
		*/
		Matrix& operator+=(const Matrix& other);
		/**	@brief %Matrix subtraction assignment operator.
		* 
		*	Subtracts the `other` matrix from the `this` matrix on a per-value basis.
		*
		*	@param other The matrix to subtract.
		*
		*	@returns A reference to itself after the assignment was complete.
		*
		*	@throws invalid_argument If the sizes of the matrices do not match.
		*/
		Matrix& operator-=(const Matrix& other);
		/**	@brief %Matrix multiplication assignment operator.
		* 
		*	Multiplies the `this` matrix by the `other` matrix and assigns the result to itself.
		*
		*	@param other The matrix to add.
		*
		*	@returns A reference to itself after the assignment was complete.
		*
		*	@throws invalid_argument If the sizes of the matrices are not appropriate for matrix multilpication.
		*/
		Matrix& operator*=(const Matrix& other);
		/**@}*/

		/** @name Comparison Operators */
		/**@{*/
		/**	@brief Equality operator.
		* 
		*	Compares the `other` matrix to the `this` matrix.
		*	Will return true only if matrices are of identical size and contain identical elements.
		*
		*	@param other %Matrix to be compared to.
		*	
		*	@returns The result of the comparison.
		*/
		bool operator==(const Matrix& other) const;
		/**	@brief Inequality operator.
		* 
		*	Compares the `other` matrix to the `this` matrix.
		*	Will return false only if matrices are of identical size and contain identical elements.
		*
		*	@param other %Matrix to be compared to.
		*
		*	@returns The result of the comparison.
		*/
		bool operator!=(const Matrix& other) const;
		/**@}*/
	};
}