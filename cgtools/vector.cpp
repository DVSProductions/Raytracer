#include "vector.h"
vector vector::operator-()noexcept {
	return vector(-x, -y, -z);
}
double vector::operator!() noexcept{
	return sqrt(x * x + y * y + z * z);
}

double vector::squaredLength()noexcept {
	return x * x + y * y + z * z;
}

bool vector::operator==(const vector &a)noexcept {
	return x == a.x && y == a.y && z == a.z;
}

double vector::operator[](const vector &b) noexcept {
	return x * b.x + y * b.y + z * b.z;
}
