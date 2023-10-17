#pragma once

#include <cmath>

namespace chcl
{
	class ContinuousSolver
	{
		float m_min, m_max, m_range;

	public:
		ContinuousSolver(float min, float max) : m_min(min), m_max(max), m_range(max - min) {}

		float clamp(float val) const;

		float diffMin(float a, float b) const;

		float avgMin(float a, float b) const;

	private:
		float offset(float val) const;
	};

	extern ContinuousSolver radianSolver, degreeSolver;
}