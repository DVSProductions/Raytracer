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
		x0 = v.x0;
		dir = v.dir;
		tmax = v.tmax;
		tmin = v.tmin;
		refractionIndex = v.refractionIndex;
		return *this;
	}
	Ray Ray::transform(cgtools::matrix translator) noexcept {
		return Ray(translator * x0, translator * dir, this->tmax, tmin);
	}
	cgtools::point Ray::getPoint(double t) const noexcept {
		return x0 + (dir * t);
	}
}
