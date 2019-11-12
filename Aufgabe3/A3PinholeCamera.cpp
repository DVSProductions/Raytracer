#include "A3PinholeCamera.h"
#include "DLLInfo.h"
A3PinholeCamera::A3PinholeCamera(double angle, const cgtools::point& position,const cgtools::Color& background)noexcept :Camera(position, angle) {
	precalculation(angle);
	this->background = background;
}

void A3PinholeCamera::precalculation(double angle)noexcept {
	w0_5 = width / 2.0;
	h0_5 = height / 2.0;
	a05tan = tan(angle / 2.0);
	zpre = -(w0_5 / a05tan);
}

DDD::Ray A3PinholeCamera::generateRay(double x, double y)noexcept {
	return DDD::Ray(cgtools::point(0, 0, 0), ~cgtools::direction(x - w0_5, h0_5 - y, zpre), INFINITY, 0);
}
cgtools::Color A3PinholeCamera::getColor(double x, double y) {
	const auto c = scene->intersect(generateRay(x, y));
	return c.hit ? c.shade() : background;
	
}

size_t A3PinholeCamera::size() const {
	return sizeof(A3PinholeCamera)+__super::size();
}

