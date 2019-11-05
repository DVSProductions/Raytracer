#include "DLLInfo.h"
#include "PinholeCamera.h"
DDD::PinholeCamera::PinholeCamera(std::string serialized) :ACamera(point(0, 0, 0), 0),background(Color(0,0,0)) {
	this->load(serialized);
}
DDD::PinholeCamera::PinholeCamera(double angle, const cgtools::point& position, DDD::Background background)noexcept :ACamera(position, angle),background(background) {
	precalculation(angle);
	this->background = background;
}

void DDD::PinholeCamera::init() noexcept {
	w0_5 = width / 2.0;
	h0_5 = height / 2.0;
	a05tan = tan(angle / 2.0);
	zpre = -(w0_5 / a05tan);
}

void DDD::PinholeCamera::precalculation(double angle)noexcept {
	init();
}

DDD::Ray DDD::PinholeCamera::generateRay(double x, double y)noexcept {
	return DDD::Ray(point(0, 0, 0), ~direction(x - w0_5, h0_5 - y, zpre), INFINITY, 0);
}
cgtools::Color DDD::PinholeCamera::getColor(double x, double y) {
	const auto r = generateRay(x, y);
	const auto c = scene->intersect(r);
	return c.hit ? c.shade() : background.intersect(r).c;
}

std::string DDD::PinholeCamera::serialize() const {
	return ACamera::includeClassID(background.serializeFast() + "[" + __super::serialize(), CLASSID);
}

void DDD::PinholeCamera::load(std::string serialized) {
	const auto s = Serializable::split(serialized, "[");
	background.load(s.at(0));
	__super::load(s.at(1));
}

