#include "vector.h"
#include <limits>
using namespace cgtools;
vector cgtools::vector::operator-(const double& d) const noexcept {
	return vector(x - d, y - d, z - d);
}
vector vector::operator-() const noexcept {
	return vector(-x, -y, -z);
}
double vector::operator!() const  noexcept {
	return sqrt(x * x + y * y + z * z);
}

double vector::squaredLength() const noexcept {
	return x * x + y * y + z * z;
}

bool vector::operator==(const vector& a) const noexcept {
	return x == a.x && y == a.y && z == a.z;
}

double vector::operator[](const vector& b) const  noexcept {
	return x * b.x + y * b.y + z * b.z;
}

double cgtools::vector::operator[](const int& b) const noexcept {
	switch (b) {
	case(0):return x;
	case(1):return y;
	case(2):return z;
	default:
		return std::numeric_limits<double>::signaling_NaN();
	}
}

double cgtools::vector::scalar(const vector& v) const noexcept {
	return (x * v.x) + (y * v.y) + (z * v.z);
}
double dostaging(int pow, double input)noexcept {
	return floor(input*pow) / pow;
}
vector cgtools::vector::reduceAccuracy(uint8_t power) const noexcept {
	const long num = static_cast<long>(pow(10,power));
	return vector(dostaging(num,x),dostaging(num,y),dostaging(num,z));
}
