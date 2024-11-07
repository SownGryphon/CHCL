#pragma once

#include <cmath>

#include "chcl/geometry/VectorN.h"

namespace chcl
{
	template <typename T>
	class ContinuousSolver
	{
		T m_min, m_max, m_range;

	public:
		ContinuousSolver(T min, T max) : m_min(min), m_max(max), m_range(max - min) {}

		T clamp(T val) const
		{
			return offset(val) * m_range + m_min;
		}

		T diffMin(T a, T b) const
		{
			T offsetA = offset(a);
			T offsetB = offset(b);
			T diff = offsetB - offsetA;
			if (diff < -0.5f)
				return (1.f + diff) * m_range;
			if (diff > 0.5f)
				return (diff - 1.f) * m_range;
			return diff * m_range;
		}

		T avgMin(T a, T b) const
		{
			T diff = diffMin(a, b);
			return clamp(a + diff / 2);
		}

	private:
		T offset(T val) const
		{
			T offset = (val - m_min) / m_range;
			return offset - std::floorf(offset);
		}
	};

	template <unsigned int dims, typename T>
	class ContinuousSolver<VectorN<dims, T>>
	{
		using VecType = VectorN<dims, T>;

		VecType m_min, m_max, m_range;

	public:
		ContinuousSolver(VecType min, VecType max) : m_min(min), m_max(max), m_range(max - min) {}

		VecType clamp(VecType val) const
		{
			return offset(val) * m_range + m_min;
		}

		VecType diffMin(VecType a, VecType b) const
		{
			VecType offsetA = offset(a);
			VecType offsetB = offset(b);
			VecType diff = offsetB - offsetA;
			static chcl::ContinuousSolver<T> diffConstrain(T(-0.5), T(0.5));
			for (unsigned int i = 0; i < dims; ++i)
				diff[i] = diffConstrain.clamp(diff[i]);
			return diff * m_range;
		}

		VecType avgMin(VecType a, VecType b) const
		{
			VecType diff = diffMin(a, b);
			return clamp(a + diff / 2);
		}

	private:
		VecType offset(VecType val) const
		{
			static chcl::ContinuousSolver<T> offsetConstrain(T(0), T(1));
			VecType offset = (val - m_min) / m_range;
			for (unsigned int i = 0; i < dims; ++i)
				offset[i] = offsetConstrain.clamp(offset[i]);
			return offset;
		}
	};

	extern ContinuousSolver<float> radianSolver, degreeSolver;
}