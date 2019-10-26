#include "Hit.h"
#include <math.h>

DDD::Hit::Hit(double t, point pos, direction n, Color c) :pos(pos), n(n) {
	this->t = t;
	this->c = c;
}

Color DDD::Hit::shade() const noexcept {
	direction lightDir = ~direction(1, 1, 0.5);
	return 0.1 * c + (0.9 * fmax(0, lightDir[n])) * c;
}
