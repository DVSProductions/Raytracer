#include "point.h"

point point::operator-() noexcept {
	return point(-x,-y,-z);
}

point point::operator-(const direction& d) noexcept {
	return point(this->x - d.x, this->y - d.y, this->z - d.z);
}


direction point::todirection()noexcept {
	return direction(x, y, z);
}

direction point::sub(const point& b) noexcept {
	return direction(this->x - b.x, this->y - b.y, this->z - b.z);
}

point operator+(const direction& d, const point& b)  noexcept {
	return point(d.x + b.x, d.y + b.y, d.z + b.z);
}

point operator+(direction d, point b)noexcept {
	return point(d.x + b.x, d.y + b.y, d.z + b.z);
}
