#include "Ray.h"

point Ray::pointAt(double t) noexcept {
	return xZero+(dir*t);
}
