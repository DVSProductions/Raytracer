#include "direction.h"
#include <math.h>
#include <string>

using namespace cgtools;
direction::direction(double x, double y, double z) noexcept :vector(x, y, z) {}

direction direction::operator+(const direction& b) const noexcept {
	return direction(this->x + b.x, this->y + b.y, this->z + b.z);
}

direction direction::operator-(const direction &b) const  noexcept {
	return direction(x - b.x, y - b.y, z - b.z);
}
direction direction::operator*(const double& s) const noexcept {
	return direction(x * s, y * s, z * s);
}

direction cgtools::direction::operator*(const vector& s) const noexcept {
	return direction(s.x*x,s.y*y,s.z*z);
}

direction direction::operator/(const double &s) const noexcept {
	return direction(x / s, y / s, z / s);
}

direction direction::operator|(const direction &b) const noexcept {
	return direction(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
}

direction direction::operator~() noexcept {
	return *this / !*this;
}
direction cgtools::direction::operator~() const noexcept {
	return *this / !*this;
}
//std::string cgtools::direction::serialize() const {
//	return  std::to_string(x) + "|" + std::to_string(y) + "|" + std::to_string(z);
//}
//void cgtools::direction::load(std::string serialized) {
//	auto ret = Serializable::split(serialized);
//	std::from_chars(ret[0].data(), ret[0].data() + ret[0].size(), x);
//	std::from_chars(ret[1].data(), ret[1].data() + ret[1].size(), y);
//	std::from_chars(ret[2].data(), ret[2].data() + ret[2].size(), z);
//}
direction operator*(double s, direction a) noexcept {
	return direction(a.x * s, a.y * s, a.z * s);
}

direction operator*(const double& s, const direction& a) noexcept {
	return direction(a.x * s, a.y * s, a.z * s);
}

direction operator-(const point& a, const point& b) noexcept {
	return direction(a.x - b.x, a.y - b.y, a.z - b.z);
}

direction cgtools::operator*(const double& s, const direction& a) noexcept {
	return direction(a.x * s, a.y * s, a.z * s);
}
