#include "cggRandom.h"

unsigned long long cggRandom::staffordMix13(unsigned long long z) {
	z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9L;
	z = (z ^ (z >> 27)) * 0x94D049BB133111EBL;
	return z ^ (z >> 31);
}

 int cggRandom::staffordMix4Upper32(unsigned long long z) {
	z = (z ^ (z >> 33)) * 0x62A9D9ED799705F5L;
	return (int)(((z ^ (z >> 28)) * 0xCB24D0A5C88C35B3L) >> 32);
}

 double cggRandom::random() {
	return generate();
}

 cggRandom::cggRandom(const long seed) {
	x = seed;
}

 long cggRandom::nextLong() {
	return staffordMix13(x += PHI);
}

 int cggRandom::nextInt() {
	return staffordMix4Upper32(x += PHI);
}

 int cggRandom::nextInt(const int n) {
	return (int)nextLong(n);
}

 long cggRandom::nextLong(const long n) {
	if (n <= 0)
		throw new std::exception(("illegal bound " + std::to_string(n) + " (must be positive)").c_str());
	auto t = staffordMix13(x += PHI);
	const auto nMinus1 = n - 1;
	if ((n & nMinus1) == 0)
		return t & nMinus1;
	for (auto u = t >> 1; u + nMinus1 - (t = u % n) < 0; u = staffordMix13(x += PHI) >> 1);
	return t;
}

 double cggRandom::generate() {
	auto l = (staffordMix13(x += PHI) >> 12) | (0x3FFUL << 52);
	double d = *reinterpret_cast<double*>(&l);
	d -= 1;
	return d;
}

 float cggRandom::nextFloat() {
	auto l = staffordMix4Upper32(x += PHI) >> 41 | 0x3F8 << 20;
	return *reinterpret_cast<double*>(&l) - 1.0f;
}

 bool cggRandom::nextBoolean() {
	return staffordMix4Upper32(x += PHI) < 0;
}
