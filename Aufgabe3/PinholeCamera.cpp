#include "PinholeCamera.h"
#include "DLLInfo.h"
PinholeCamera::PinholeCamera(double angle, const point& position) :Camera(position, angle) {
	w0_5 = width / 2.0;
	h0_5 = height / 2.0;
	a05tan = tan(angle / 2.0);
	zpre = -(w0_5 / a05tan);
}

Color PinholeCamera::getColor(double x, double y) {
	auto c= scene->intersect(generateRay(x, y));
	if (c == nullptr) 
		return cgtools::c_gray;
	else return c->shade();
}

DDD::Ray PinholeCamera::generateRay(double x, double y) {
	return DDD::Ray(point(0, 0, 0), ~direction(x - w0_5, h0_5 - y, zpre), INFINITY, 0);
}
