#include "DLLInfo.h"
#include "PinholeCamera.h"
DDD::PinholeCamera::PinholeCamera(double angle, const cgtools::point& position, const cgtools::Color& background)noexcept :ACamera(position, angle) {
	precalculation(angle);
	this->background = background;
}

void DDD::PinholeCamera::precalculation(double angle)noexcept {
	w0_5 = width / 2.0;
	h0_5 = height / 2.0;
	a05tan = tan(angle / 2.0);
	zpre = -(w0_5 / a05tan);
}

DDD::Ray DDD::PinholeCamera::generateRay(double x, double y)noexcept {
	return DDD::Ray(point(0, 0, 0), ~direction(x - w0_5, h0_5 - y, zpre), INFINITY, 0);
}
cgtools::Color DDD::PinholeCamera::getColor(double x, double y) {
	const auto c = scene->intersect(generateRay(x, y));
	return c.hit ? c.shade() : background;

}

std::string DDD::PinholeCamera::serialize() const {
	return this->background.serialize()+"["+__super::serialize();
}

void DDD::PinholeCamera::load(std::string serialized) {
	const auto s=Serializable::split(serialized,"[");
	background.load(s[0]);
	__super::load(s[1]);
}

