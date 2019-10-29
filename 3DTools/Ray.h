#pragma once
#include "direction.h"
#include "point.h"
using namespace cgtools;
namespace DDD {
	struct Ray {
	public:
		const point x0;
		const direction dir;
		const double tmin, tmax;
		Ray(point p, direction d, double max, double min) noexcept;
		point pointAt(double t)const noexcept;
	};
}