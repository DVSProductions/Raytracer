#include "point.h"
namespace cgtools {
	point::operator std::string() const {
		return "(point[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "])";
	}
	point point::operator-() noexcept {
		return point(-x, -y, -z);
	}

	point point::operator-(const point& p) const noexcept {
		return point(x - p.x, y - p.y, z - p.z);
	}

	point point::operator-(const direction& d) noexcept {
		return point(this->x - d.x, this->y - d.y, this->z - d.z);
	}


	point point::operator+(const direction& d) const noexcept {
		return point(this->x + d.x, this->y + d.y, this->z + d.z);
	}


	direction point::todirection()noexcept {
		return direction(x, y, z);
	}

	direction point::sub(const point& b) noexcept {
		return direction(this->x - b.x, this->y - b.y, this->z - b.z);
	}

	point point::operator*(const vector& s) const noexcept {
		return point(x * s.x, y * s.y, z * s.z);
	}
	direction point::operator/(const double& d) const noexcept {
		return direction(x / d, y / d, z / d);
	}
	size_t point::size() const {
		return sizeof(point);
	}

	//point operator+(const direction& d, const point& b)  noexcept {
	//	return point(d.x + b.x, d.y + b.y, d.z + b.z);
	//}

	//point operator+(direction d, point b)noexcept {
	//	return point(d.x + b.x, d.y + b.y, d.z + b.z);
	//}
}