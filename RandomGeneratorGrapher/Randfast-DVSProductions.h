#pragma once
#include <inttypes.h>
class randfast {
	uint_fast64_t internal_next;
	uint64_t custom_lcg();
	double generate();
public:
	randfast(uint64_t seed);
	double operator() ();
	double operator()(double min, double max);
};

