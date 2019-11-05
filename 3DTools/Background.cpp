#include "Background.h"
#include "point.h"
DDD::Background::Background(std::string serialized) :renderable(point(0, 0, 0)) {
	c = cgtools::Color();
	load(serialized);
}
DDD::Background::Background(cgtools::Color color) noexcept :renderable(point{ 0,0,0 }) {
	c = color;
}

DDD::Hit DDD::Background::intersect(Ray r) const {
	return DDD::Hit(r.tmax, r.dir * r.tmax, r.dir, this->c);
}

std::string DDD::Background::serialize() const {
	return renderable::includeClassID(c.serialize(), Background::CLASSID);
}

std::string DDD::Background::serializeFast() const {
	return c.serialize();
}

void DDD::Background::load(std::string serialized) {
	c.load(serialized);
}

DDD::Background DDD::Background::operator=(const Background& b) noexcept {
	this->c = b.c;
	this->p = b.p;
	return *this;
}
