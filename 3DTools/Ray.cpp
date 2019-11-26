#include "Ray.h"
namespace DDD {
	Ray::Ray(cgtools::point p, cgtools::direction d, double max, double min)noexcept :x0(p), dir(d), tmin(min), tmax(max) {}

	Ray::Ray(cgtools::point p, cgtools::direction d, double max, double min, double refractionIndex) noexcept :Ray(p, d, max, min) {
		this->refractionIndex = refractionIndex;
	}

	cgtools::point Ray::pointAt(double t) const noexcept {
		return x0 + (dir * t);
	}
	const Ray Ray::operator=(const Ray& v) noexcept {
		this->x0 = v.x0;
		this->dir = v.dir;
		this->tmax = v.tmax;
		this->tmin = v.tmin;
		this->refractionIndex = v.refractionIndex;
		return *this;
	}
}
