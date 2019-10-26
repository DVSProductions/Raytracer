#pragma once
#include "direction.h"
#include "point.h"
using namespace cgtools;
namespace DDD {
	struct Ray {
	public:
		const point x0;
		const direction dir;
		const double tmin;
		const double tmax;
		Ray(point p, direction d, double max, double min);
		point pointAt(double t) noexcept;
	};
}