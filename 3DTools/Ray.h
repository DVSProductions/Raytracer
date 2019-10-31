#pragma once
#include "direction.h"
#include "point.h"
namespace DDD {
	struct Ray {
	public:
		const cgtools::point x0;
		const cgtools::direction dir;
		const double tmin, tmax;
		Ray(cgtools::point p, cgtools::direction d, double max, double min) noexcept;
		cgtools::point pointAt(double t)const noexcept;
	};
}