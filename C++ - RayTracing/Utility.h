#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include "Ray.h"
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double DegToRad(double degrees)
{
	return degrees * pi / 180.0;
}

inline double Random()
{
	return rand() / (RAND_MAX + 1.0);
}

inline double Random(double min, double max)
{
	return min + (max - min) * Random();
}

