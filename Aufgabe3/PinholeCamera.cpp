#include "PinholeCamera.h"
#include "DLLInfo.h"
PinholeCamera::PinholeCamera(double angle, const point& position,const Color& background)noexcept :Camera(position, angle) {
	precalculation(angle);
	this->background = background;
}

void PinholeCamera::precalculation(double angle)noexcept {
	w0_5 = width / 2.0;
	h0_5 = height / 2.0;
	a05tan = tan(angle / 2.0);
	zpre = -(w0_5 / a05tan);
}

DDD::Ray PinholeCamera::generateRay(double x, double y)noexcept {
	return DDD::Ray(point(0, 0, 0), ~direction(x - w0_5, h0_5 - y, zpre), INFINITY, 0);
}
Color PinholeCamera::getColor(double x, double y) {
	const auto c = scene->intersect(generateRay(x, y));
	return c.hit ? c.shade() : background;
	
}

