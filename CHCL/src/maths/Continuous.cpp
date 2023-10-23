#include "Continuous.h"

#include "Common.h"

chcl::ContinuousSolver<float> chcl::radianSolver(-PI, PI);
chcl::ContinuousSolver<float> chcl::degreeSolver(0, 360);