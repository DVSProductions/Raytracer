#include "Ray.h"
using namespace DDD;
Ray::Ray(point p, direction d, double max, double min)noexcept :x0(p), dir(d), tmin(min), tmax(max) {

}

point Ray::pointAt(double t) const noexcept {
	return x0 + (dir * t);
}
