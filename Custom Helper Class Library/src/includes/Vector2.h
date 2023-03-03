#pragma once

#include "Matrix.h"

namespace chcl
{
	struct Vector2
	{
		float x,	/**< @brief Vector x position. */
			y;		/**< @brief Vector y position. */

		/**	@name Constructors */
		/**@{*/
		/**	@brief Default constructor.
		* 
		*	Constructs a vector with `x` and `y` set to 0.
		*/
		Vector2();

		/**	@brief Single argument constructor.
		* 
		*	Constructs a vector with `x` and `y` set to the same value.
		* 
		*	@param num The value to set `x` and `y` to.
		*/
		Vector2(float num);

		/**	@brief Coordinate constructor.
		* 
		*	Creates a vector with set `x` and `y` values.
		* 
		*	@param x The value to set `x` to.
		*	@param y The value to set `y` to.
		*/
		Vector2(float x, float y);
		/**@}*/

		/**	@brief X component vector.
		*	
		*	@returns A vector containing the `x` component of the `this` vector.
		*/
		Vector2 xVector() const;
		/**	@brief Y component vector.
		* 
		*	@returns A vector2 containing the `y` component of the `this` vector.
		*/
		Vector2 yVector() const;

		/**	@brief Column matrix conversion.
		* 
		*	Converts the vector to a 2x1 column Matrix.
		* 
		*	@returns A 2x1 Matrix representation of the vector.
		*/
		Matrix asColMatrix() const;

		/**	@brief Vector magnitude.
		* 
		*	@returns The magnitude of the `this` vector.
		* 
		*	@remark Only use if the actual magnitude is needed. Use magsq() where possible.
		*/
		float mag() const;
		/**	@brief Squared vector magnitude.
		* 
		*	Returns the squared magnitude of the `this` vector. Use this where possible to avoid unnecessary [sqrt()](@ref std::sqrt()) calls.
		* 
		*	@returns The squared magnitude of the `this` vector.
		* 
		*	@see mag()
		*/
		float magsq() const;

		/**	@name Arithmetic Operators */
		/**@{*/
		/**	@brief Vector addition operator.
		* 
		*	Returns the sum of the `x` and `y` components of the two vectors.
		* 
		*	@param lhs The vector that will be added to.
		*	@param rhs The vector that will be added.
		* 
		*	@returns The result of the addition.
		*/
		friend Vector2 operator+(Vector2 lhs, const Vector2& rhs);
		/**	@brief Vector sutraction operator.
		* 
		*	Returns the difference between the `x` and `y` components of the two vectors.
		*
		*	@param lhs The vector that will be subtracted from.
		*	@param rhs The vector that will be subtracted.
		*
		*	@returns The result of the subtraction.
		*/
		friend Vector2 operator-(Vector2 lhs, const Vector2& rhs);
		/**	@brief Vector multilpication operator.
		* 
		*	Returns the product of the `x` and `y` components of the two vectors.
		*
		*	@param lhs The vector that will be multiplied.
		*	@param rhs The vector that will be multiplied by.
		*
		*	@returns The result of the multilpication.
		* 
		*	@remark This returns the individual products of the `x` and `y` values. It is not a dot- or cross-product.
		*	@see dot()
		*	@see cross()
		*/
		friend Vector2 operator*(Vector2 lhs, const Vector2& rhs);
		/**	@brief Vector division operator.
		* 
		*	Returns the quotient of the `x` and `y` components of the two vectors.
		*
		*	@param lhs The vector that will be divided.
		*	@param rhs The vector that will be divided by.
		*
		*	@returns The result of the division.
		*/
		friend Vector2 operator/(Vector2 lhs, const Vector2& rhs);

		/**	@brief Float addition operator.
		* 
		*	Returns the sum of the `x` and `y` components of the `vec` vector and `val`.
		*
		*	@param vec The vector that will be added to.
		*	@param val The value that will be added.
		*
		*	@returns The result of the addition.
		*
		*	@remark Eqivalent to `vec + Vector2(val)`.
		*/
		friend Vector2 operator+(Vector2 vec, float val);
		/**	@brief Float subtraction operator.
		* 
		*	Returns the difference between the `x` and `y` components of the `vec` vector and `val`.
		*
		*	@param vec The vector that will be subtracted from.
		*	@param val The value that will be subtracted.
		*
		*	@returns The result of the subtraction.
		*
		*	@remark Eqivalent to `vec - Vector2(val)`.
		*/
		friend Vector2 operator-(Vector2 vec, float val);
		/**	@brief Float multilpication operator.
		* 
		*	Returns the product of the `x` and `y` components of the `vec` vector and `val`.
		*
		*	@param vec The vector that will be multilpied.
		*	@param val The value that will be multiplied by.
		*
		*	@returns The result of the multiplication.
		*
		*	@remark Eqivalent to `vec * Vector2(val)`.
		*/
		friend Vector2 operator*(Vector2 vec, float val);
		/**	@brief Float division operator.
		* 
		*	Returns the quotient of the `x` and `y` components of the `vec` vector and `val`.
		*
		*	@param vec The vector that will be divided.
		*	@param val The value that will be divided by.
		*
		*	@returns The result of the division.
		*
		*	@remark Eqivalent to `vec / Vector2(val)`.
		*/
		friend Vector2 operator/(Vector2 vec, float val);
		/**	@brief Float addition operator.
		* 
		*	Returns the sum of the `x` and `y` components of the `vec` vector and `val`.
		*
		*	@param val The value that will be added to.
		*	@param vec The vector that will be added.
		*
		*	@returns The result of the addition.
		*
		*	@remark Eqivalent to `Vector2(val) + vec`.
		*/
		friend Vector2 operator+(float val, Vector2 vec);
		/**	@brief Float subtraction operator.
		* 
		*	Returns the difference between `val` and the `x` and `y` components of the `vec` vector.
		*
		*	@param val The value that will be subtracted from.
		*	@param vec The vector that will be subtracted.
		*
		*	@returns The result of the subtraction.
		*
		*	@remark Eqivalent to `Vector2(val) - vec`.
		*/
		friend Vector2 operator-(float val, Vector2 vec);
		/**	@brief Float multilpication operator.
		* 
		*	Returns the product of the `x` and `y` components of the `vec` vector and `val`.
		*
		*	@param vec The vector that will be multilpied.
		*	@param val The value that will be multiplied by.
		*
		*	@returns The result of the multiplication.
		*
		*	@remark Eqivalent to `Vector2(val) * vec`.
		*/
		friend Vector2 operator*(float val, Vector2 vec);
		/**	@brief Float division operator.
		* 
		*	Returns the quotient of `val` and the `x` and `y` components of the `val` vector.
		*
		*	@param val The value that will be divided.
		*	@param vec The vector that will be divided by.
		*
		*	@returns The result of the division.
		*
		*	@remark Eqivalent to `Vector2(val) / vec`.
		*/
		friend Vector2 operator/(float val, Vector2 vec);

		/**	@brief Vector dot product.
		* 
		*	@param other The vector to get the dot product with.
		* 
		*	@returns The dot product of the two vectors.
		*/
		float dot(const Vector2& other) const;
		/**	@brief Vector cross product.
		* 
		*	@param other The vector to get the cross product with.
		* 
		*	@returns The cross product of the two vectors.
		*/
		Vector2 cross(const Vector2& other) const;	// TODO: Implement vector cross product.
		/**@}*/

		/**	@name Assignment Operators */
		/**@{*/
		Vector2& operator =(const Vector2& other);
		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator*=(const Vector2& other);
		Vector2& operator/=(const Vector2& other);
		/**@}*/

		/**	@brief Normalised vector.
		*	
		*	@returns The normalised version of the vector (magnitude of 1).
		*/
		Vector2 normalised() const;

		/**	@name Comparison Operators */
		/**@{*/
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		/**@}*/
	};
}