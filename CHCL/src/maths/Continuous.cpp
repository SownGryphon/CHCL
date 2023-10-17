#include "Continuous.h"

#include "Common.h"

namespace chcl
{
	ContinuousSolver radianSolver(-PI<float>, PI<float>);
	ContinuousSolver degreeSolver(0, 360);

	float ContinuousSolver::clamp(float val) const
	{
		return offset(val) * m_range + m_min;
	}

	float ContinuousSolver::diffMin(float a, float b) const
	{
		float offsetA = offset(a);
		float offsetB = offset(b);
		float diff = offsetB - offsetA;
		if (diff < -0.5f)
			return (1.f + diff) * m_range;
		if (diff > 0.5f)
			return (diff - 1.f) * m_range;
		return diff * m_range;
	}

	float ContinuousSolver::avgMin(float a, float b) const
	{
		float diff = diffMin(a, b);
		return clamp(a + diff / 2);
	}

	float ContinuousSolver::offset(float val) const
	{
		float offset = (val - m_min) / m_range;
		return offset - std::floorf(offset);
	}
}