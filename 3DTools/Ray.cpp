#include "Ray.h"
using namespace DDD;
Ray::Ray(point p, direction d, double max, double min) :x0(p), dir(d), tmin(min), tmax(max) {

}

point Ray::pointAt(double t) noexcept {
	return x0 + (dir * t);
}
