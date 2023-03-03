#pragma once

#include <stdexcept>
#include <cmath>

#include "Matrix.h"

#define tVecNTemplate template <unsigned int dims>

namespace chcl
{
	tVecNTemplate
	struct tVectorN;

	tVecNTemplate tVectorN<dims> operator+(tVectorN<dims> lhs, const tVectorN<dims>& rhs);
	tVecNTemplate tVectorN<dims> operator-(tVectorN<dims> lhs, const tVectorN<dims>& rhs);
	tVecNTemplate tVectorN<dims> operator*(tVectorN<dims> lhs, float val);
	tVecNTemplate tVectorN<dims> operator/(tVectorN<dims> lhs, float val);
	tVecNTemplate tVectorN<dims> operator*(float val, tVectorN<dims> lhs);

	tVecNTemplate
	struct tVectorN
	{
		float position[dims];	/**< @brief Array storing the vector's position. */

		/** @name Constructors */
		/**@{*/
		/**	@brief Default constructor.
		* 
		*	Constructs a vector with a blank position array.
		*/
		tVectorN();

		/**	@brief Single value constructor.
		* 
		*	Constructs a vector filled with a value.
		* 
		*	@param val Value to fill the position array with.
		*/
		tVectorN(float val);

		/**	@brief Position copy constructor.
		* 
		*	Constructs a vector in a given position.
		* 
		*	@param position The position to create the vector at.
		*/
		tVectorN(float position[dims]);

		/**	Initializer list constructor.
		*/
		tVectorN(const float (&list)[dims]);

		/**	@brief Copy constructor. */
		tVectorN(const tVectorN& other);
		/**@}*/

		/**	@brief Vector component getter.
		* 
		*	@returns The component of the vector along the given dimension axis.
		*/
		tVectorN component(unsigned int dimension) const;

		/**	@brief Vector magnitude.
		*
		*	@returns The magnitude of the vector.
		*
		*	@remark Only use if the actual magnitude is needed. Use magsq() where possible.
		*/
		float mag() const;
		/**	@brief Squared vector magnitude.
		*
		*	Returns the squared magnitude of the vector. Use this where possible to avoid unnecessary [sqrt()](@ref std::sqrt()) calls.
		*
		*	@returns The squared magnitude of the vector.
		*
		*	@see mag()
		*/
		float magsq() const;

		/**	@brief Column matrix conversion.
		* 
		*	@returns The vector represented as a column matrix.
		*/
		Matrix toMatrix() const;

		/**	@brief Converts column matrix to vector.
		*/
		static tVectorN fromMatrix(const Matrix& matrix);

		template <unsigned int otherDims>
		static tVectorN upscale(const tVectorN<otherDims>& other);

		tVectorN normalised() const;

		/**	@brief Vector dot product.
		* 
		*	@param other The vector to calculate the dot product with.
		* 
		*	@returns The dot product of the two vectors.
		*/
		float dot(const tVectorN& other) const;

		/**	@name Arithmetic Operators */
		/**@{*/
		friend tVectorN operator+ <>(tVectorN lhs, const tVectorN& rhs);
		friend tVectorN operator- <>(tVectorN lhs, const tVectorN& rhs);

		friend tVectorN operator* <>(tVectorN vec, float val);
		friend tVectorN operator/ <>(tVectorN vec, float val);
		friend tVectorN operator* <>(float val, tVectorN vec);
		/**@}*/

		/**	@name Assignment Operators */
		/**@{*/
		tVectorN& operator =(const tVectorN& other);
		tVectorN& operator+=(const tVectorN& other);
		tVectorN& operator-=(const tVectorN& other);

		tVectorN& operator*=(float val);
		tVectorN& operator/=(float val);
		/**@}*/
	};

	tVecNTemplate tVectorN<dims>::tVectorN()
	{
		for (unsigned int i = 0; i < dims; ++i)
		{
			position[i] = 0.f;
		}
	}

	tVecNTemplate tVectorN<dims>::tVectorN(float val)
	{
		for (unsigned int i = 0; i < dims; ++i)
		{
			position[i] = val;
		}
	}
	
	tVecNTemplate tVectorN<dims>::tVectorN(float position[dims])
	{
		std::memcpy(this->position, position, sizeof(float) * dims);
	}

	tVecNTemplate tVectorN<dims>::tVectorN(const float(&list)[dims])
	{
		memcpy(position, &list, sizeof(float) * dims);
	}
	
	tVecNTemplate tVectorN<dims>::tVectorN(const tVectorN<dims>& other)
	{
		for (unsigned int i = 0; i < dims; ++i)
		{
			this->position[i] = other.position[i];
		}
	}

	tVecNTemplate tVectorN<dims> tVectorN<dims>::component(unsigned int dimension) const
	{
		tVectorN result{};

		result.position[dimension] = position[dimension];

		return result;
	}

	tVecNTemplate tVectorN<dims> tVectorN<dims>::fromMatrix(const Matrix& matrix)
	{
		if (matrix.getCols() != 1 || matrix.getRows() != dims)
		{
			throw std::invalid_argument("Matrix is not the right size for vector construction.");
		}

		tVectorN<dims> result{};

		for (unsigned int i = 0; i < dims; ++i)
		{
			result.position[i] = matrix.values[i];
		}

		return result;
	}

	tVecNTemplate template <unsigned int otherDims>
	tVectorN<dims> tVectorN<dims>::upscale(const tVectorN<otherDims>& other)
	{
		if (otherDims >= dims)
		{
			throw std::invalid_argument("Trying to upscale a higher-dimension vector.");
		}

		tVectorN<dims> result{};

		memcpy(result.position, other.position, sizeof(float) * otherDims);

		return result;
	}

	tVecNTemplate tVectorN<dims> tVectorN<dims>::normalised() const
	{
		return *this / mag();
	}

	tVecNTemplate Matrix tVectorN<dims>::toMatrix() const
	{
		Matrix result{ 1, dims, (float*) position };

		return result;
	}

	tVecNTemplate float tVectorN<dims>::magsq() const
	{
		float total = 0;

		for (unsigned int i = 0; i < dims; ++i)
		{
			total += position[i] * position[i];
		}

		return total;
	}

	tVecNTemplate float tVectorN<dims>::mag() const
	{
		return std::sqrtf(magsq());
	}

	tVecNTemplate float tVectorN<dims>::dot(const tVectorN& other) const
	{
		float total = 0;

		for (unsigned int i = 0; i < dims; ++i)
		{
			total += position[i] * other.position[i];
		}

		return total;
	}

	tVecNTemplate tVectorN<dims>& tVectorN<dims>::operator=(const tVectorN& other)
	{
		std::memcpy(this->position, other.position, sizeof(float) * dims);

		return *this;
	}

	tVecNTemplate tVectorN<dims>& tVectorN<dims>::operator+=(const tVectorN& other)
	{
		for (unsigned int i = 0; i < dims; ++i)
		{
			this->position[i] += other.position[i];
		}

		return *this;
	}

	tVecNTemplate tVectorN<dims>& tVectorN<dims>::operator-=(const tVectorN& other)
	{
		for (unsigned int i = 0; i < dims; ++i)
		{
			this->position[i] -= other.position[i];
		}

		return *this;
	}

	tVecNTemplate tVectorN<dims>& tVectorN<dims>::operator*=(float val)
	{
		for (unsigned int i = 0; i < dims; ++i)
		{
			position[i] *= val;
		}

		return *this;
	}

	tVecNTemplate tVectorN<dims>& tVectorN<dims>::operator/=(float val)
	{
		for (unsigned int i = 0; i < dims; ++i)
		{
			position[i] /= val;
		}

		return *this;
	}

	tVecNTemplate tVectorN<dims> operator+(tVectorN<dims> lhs, const tVectorN<dims>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	tVecNTemplate tVectorN<dims> operator-(tVectorN<dims> lhs, const tVectorN<dims>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	tVecNTemplate tVectorN<dims> operator*(tVectorN<dims> vec, float val)
	{
		vec *= val;
		
		return vec;
	}

	tVecNTemplate tVectorN<dims> operator*(float val, tVectorN<dims> vec)
	{
		vec *= val;
		
		return vec;
	}

	tVecNTemplate tVectorN<dims> operator/(tVectorN<dims> vec, float val)
	{
		vec /= val;
		
		return vec;
	}
}