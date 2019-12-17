#include <string>
#include "Plane.h"
#include "Vanta.h"
#include "../cgtools/vector.h"
DDD::Plane::Plane(std::string serialized) : renderable(cgtools::point(0, 0, 0)), n(0, 0, 0) {
	load(serialized);
}

DDD::Plane::Plane(cgtools::point position, cgtools::direction dir, std::shared_ptr<AMaterial> mat) noexcept : renderable(position), n(dir) {
	Material = mat;
}
DDD::Plane::Plane(cgtools::point postion, cgtools::direction dir, std::shared_ptr<AMaterial>  mat, double radius) noexcept : Plane(postion, dir, mat) {
	r = radius;
}

DDD::Plane::Plane(cgtools::point position, cgtools::direction dir, cgtools::Color color) : Plane(position, dir, std::make_shared<Vanta>(Vanta(color))) {}
DDD::Plane::Plane(cgtools::point position, cgtools::direction dir, cgtools::Color color, double radius) : Plane(position, dir, color) {
	r = radius;
}



DDD::Hit DDD::Plane::intersect(Ray r) const noexcept {
	const auto x0 = r.x0 - p;
	const auto a = x0[n];
	const auto b = r.dir[n];
	const auto t = -(a / b);
	const auto hitpoint = r.pointAt(t);
	if (this->r != -1 && (!(p - hitpoint)) > this->r)
		return Hit();
	if (t > r.tmax || t < r.tmin)return Hit();
	return Hit(t, hitpoint, n, Material);
}

std::string DDD::Plane::serialize() const {
	return renderable::includeClassID(std::to_string(r) + "&" + n.serialize() + "&" + Material->serialize() + "&" + p.serialize() + "&", Plane::CLASSID);
}

void DDD::Plane::load(std::string serialized) {
	auto ret = Serializable::split(serialized, "&");
	f_chars(ret.at(0), r);
	n.load(ret.at(1));
	n = ~n;
	Material = std::shared_ptr<AMaterial>(AMaterial::createFromSerialization(ret.at(2)));
	p.load(ret.at(3));
}

DDD::renderable* DDD::Plane::clone() const {
	return new Plane(p, n, Material, r);
}

size_t DDD::Plane::size() const noexcept {
	return sizeof(DDD::Plane);
}