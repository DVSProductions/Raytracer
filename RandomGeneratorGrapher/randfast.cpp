#include "randfast.h"
#include <float.h>

#define SHR_BIT (64 - (DBL_MANT_DIG-1))
uint64_t randfast::custom_lcg() {
	return internal_next = internal_next * 2862933555777941757ULL + 3037000493ULL;
}

randfast::randfast(uint64_t seed) {
	internal_next = seed;
}

double randfast::generate() {
	union {
		double f; uint64_t i;
	}u;
	u.f = 1.0;
	u.i = u.i | (custom_lcg() >> SHR_BIT);
	return u.f - 1.0;
}

double randfast::operator()() {
	return generate();
}

double randfast::operator()(double min, double max) {
	return generate() * (max - min) + min;
}
