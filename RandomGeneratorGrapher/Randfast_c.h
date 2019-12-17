#pragma once
/// <summary>
/// https://stackoverflow.com/a/29485641/4203189
/// </summary>
#include <float.h>
#include <cstdint>
#define RANDMAX (-1ULL)
uint64_t custom_lcg(uint_fast64_t* next) {
	return *next = *next * 2862933555777941757ULL + 3037000493ULL;
}

uint_fast64_t internal_next;
void seed_fast(uint64_t seed) {
	internal_next = seed;
}

double rand_fast(void) {
#define SHR_BIT (64 - (DBL_MANT_DIG-1))
	union {
		double f; uint64_t i;
	} u;
	u.f = 1.0;
	u.i = u.i | (custom_lcg(&internal_next) >> SHR_BIT);
	return u.f - 1.0;
}
double rand_dist(double min, double max) {
	return rand_fast() * (max - min) + min;
}
