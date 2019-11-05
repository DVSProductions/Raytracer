#include "Ray.h"
using namespace DDD;
Ray::Ray(cgtools::point p, cgtools::direction d, double max, double min)noexcept :x0(p), dir(d), tmin(min), tmax(max) {}

cgtools::point Ray::pointAt(double t) const noexcept {
	return x0 + (dir * t);
}
