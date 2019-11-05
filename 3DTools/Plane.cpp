#include "Plane.h"
#include <string>
#include "vector.h"
DDD::Plane::Plane(std::string serialized) : renderable(point(0, 0, 0)), n(0, 0, 0) {
	load(serialized);
}

DDD::Plane::Plane(cgtools::point position, cgtools::direction dir, cgtools::Color color)noexcept : renderable(position), n(dir) {
	this->c = color;
}

DDD::Plane::Plane(cgtools::point position, cgtools::direction dir, cgtools::Color color, double radius) noexcept :Plane(position, dir, color) {
	r = radius;
}

DDD::Hit DDD::Plane::intersect(Ray r) const {
	const auto x0 = r.x0 - p;
	const auto a = x0[n];
	const auto b = r.dir[n];
	const auto t = -(a / b);
	const auto hitpoint = r.pointAt(t);
	if (this->r != -1 && !(p - hitpoint) > this->r)
		return Hit(false);
	if (t > r.tmax || t < r.tmin)return Hit(false);
	return Hit(t, hitpoint, ~n, c);
}

std::string DDD::Plane::serialize() const {
	return renderable::includeClassID(std::to_string(r)+"&"+n.serialize() + "&" + c.serialize() + "&" + p.serialize() + "&", Plane::CLASSID);
}

void DDD::Plane::load(std::string serialized) {
	auto ret = Serializable::split(serialized, "&");
	f_chars(ret.at(0), r);
	n.load(ret.at(1));
	c.load(ret.at(2));
	p.load(ret.at(3));
}
