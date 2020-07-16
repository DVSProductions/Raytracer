#include "direction.h"
#include <math.h>
#include <string>

namespace cgtools {
	direction::direction(double x, double y, double z) noexcept :vector(x, y, z) {}

	direction::operator std::string() const {
		return "(direction[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "])";
	}

	direction direction::operator+(const direction& d) const noexcept {
		return direction(x + d.x, y + d.y, z + d.z);
	}

	direction direction::operator-(const direction& d) const noexcept {
		return direction(x - d.x, y - d.y, z - d.z);
	}
	direction direction::operator-() const noexcept {
		return direction(-x, -y, -z);
	}
	direction direction::operator*(const double& s) const noexcept {
		return direction(x * s, y * s, z * s);
	}

	direction direction::operator*(const point& v) const noexcept {
		return direction(v.x * x, v.y * y, v.z * z);
	}

	direction direction::operator/(const double& s) const noexcept {
		return direction(x / s, y / s, z / s);
	}

	direction direction::operator|(const direction& b) const noexcept {
		return direction(this->y * b.z - this->z * b.y, this->z * b.x - this->x * b.z, this->x * b.y - this->y * b.x);
	}

	direction direction::operator~() const noexcept {
		return *this / !(*this);
	}
	point direction::operator+(const point& p)const noexcept {
		return point(x + p.x, y + p.y, z + p.z);
	}
	point direction::operator+(point p) const noexcept {
		return point(x + p.x, y + p.y, z + p.z);
	}
	size_t direction::size() const {
		return sizeof(direction);
	}
	direction operator*(const double& s, const direction& a) noexcept {
		return direction(a.x * s, a.y * s, a.z * s);
	}
}