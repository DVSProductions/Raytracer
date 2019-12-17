/**
 * @author henrik.tramberend@beuth-hochschule.de
 */
#include <exception>
#include <string>
 /**
  * A faster replacement for java.util.Random.
  *
  * Adapted from
  * http://dsiutils.di.unimi.it/docs/it/unimi/dsi/util/SplitMix64Random.html
  */
class cggRandom {
private:
	const unsigned long long PHI = 0x9E3779B97F4A7C15L;
	unsigned long long x=0;
	unsigned long long staffordMix13(unsigned long long z);
	int staffordMix4Upper32(unsigned long long z);
public:
	double random();
	cggRandom(const long seed);
	long nextLong();
	int nextInt();
	int nextInt(const int n);
	long nextLong(const long n);
	double generate();
	float nextFloat();
	bool nextBoolean();
};
