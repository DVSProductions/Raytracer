#include "Background.h"
#include "point.h"
#include <memory.h>
DDD::Background::Background(std::string serialized) :renderable(cgtools::point(0, 0, 0)) {
	Material = std::make_shared<Vanta>(Vanta(cgtools::Color(0, 0, 0)));
	load(serialized);
}
DDD::Background::Background(cgtools::Color color) noexcept :renderable(cgtools::point{ 0,0,0 }) {
	Material = std::make_shared<Vanta>(Vanta(color));
}

DDD::Hit DDD::Background::intersect(Ray r) const {
	return DDD::Hit(r.tmax, r.dir * r.tmax, r.dir, Material);
}

std::string DDD::Background::serialize() const {
	return renderable::includeClassID(Material->serialize(), Background::CLASSID);
}

std::string DDD::Background::serializeFast() const {
	return Material->serialize();
}

void DDD::Background::load(std::string serialized) {
	Material->load(serialized);
}

DDD::Background DDD::Background::operator=(const Background& b) noexcept {
	this->Material = b.Material;
	this->p = b.p;
	return *this;
}

DDD::renderable* DDD::Background::clone() const {
	return new Background(Material->emission);
}

size_t DDD::Background::size() const {
	return sizeof(DDD::Background);
}
