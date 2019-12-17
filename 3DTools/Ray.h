#pragma once
#include "../cgtools/direction.h"
#include "../cgtools/point.h"
#include "../cgtools/Matrix.h"
namespace DDD {
	struct Ray {
	public:
		cgtools::point x0;
		cgtools::direction dir;
		double tmin, tmax = -INFINITY;
		double refractionIndex = 1;
		Ray(cgtools::point p, cgtools::direction d, double max, double min) noexcept;
		Ray(cgtools::point p, cgtools::direction d, double max, double min, double refractionIndex) noexcept;
		cgtools::point pointAt(double t)const noexcept;
		const Ray operator=(const Ray& v) noexcept;
		Ray transform(cgtools::matrix translator)noexcept;
	};
}