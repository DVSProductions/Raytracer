#include "Hit.h"
#include <math.h>
DDD::Hit::Hit(bool hit)noexcept : pos(0, 0, 0), n(0, 0, 0) {
	this->hit = false;
}
DDD::Hit::Hit(double t, point pos, direction n, Color c)noexcept :pos(pos), n(n) {
	this->t = t;
	this->c = c;
	this->hit = true;
}

Color DDD::Hit::shade() const noexcept {
	return 0.1 * c + (0.9 * fmax(0, (~direction(1, 1, 0.5))[n])) * c;
}
