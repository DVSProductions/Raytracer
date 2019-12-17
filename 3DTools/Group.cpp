#include "Group.h"

DDD::Group::Group(std::string serialized) :renderable(cgtools::point(0, 0, 0)) {
	load(serialized);
}

DDD::Group::Group(cgtools::point position) : renderable(position) {
	objects = std::make_unique <std::vector <DDD::renderable*>>();
}

DDD::Group::~Group() { clear(); }

void DDD::Group::addObject(DDD::renderable* obj) {
	objects->push_back(obj);
}

void DDD::Group::clear()noexcept {
	try {
		const auto end = objects->size();
		for (size_t n = 0; n != end; n++)
			delete[](objects->at(n));
		objects->clear();
		_CATCH_ALL
	}
}

DDD::Hit DDD::Group::intersect(Ray r) const {
	Hit closest = Hit();
	const auto offsetRay = Ray(r.x0 - p, r.dir, r.tmax, r.tmin);
	const auto end = objects->end();
	for (auto it = objects->begin(); it != end; it++) {
		const auto h = (*it)->intersect(offsetRay);
		if (h.hit && (!closest.hit || h.t < closest.t))
			closest = h;
	}
	return closest;
}

std::string DDD::Group::serialize() const {
	//const size_t siz = this->objects->size();
	std::string ret = this->p.serialize() + "$";
	for (auto e : *objects)
		ret += e->serialize() + "$";
	return renderable::includeClassID(ret, CLASSID);
}

void DDD::Group::load(std::string serialized) {
	auto ch = Serializable::split(serialized, "$");
	this->p.load(ch.at(0));
	const size_t siz = ch.size();
	this->clear();
	for (size_t n = 1; n < siz; n++)
		objects->push_back(renderable::createFromSerialization(ch.at(n)));
}

DDD::renderable* DDD::Group::clone() const {
	const auto ret = new Group(p);
	const auto end = objects->end();
	for (auto it = objects->begin(); it != end; it++)
		ret->addObject((*it)->clone());
	return ret;
}

size_t DDD::Group::size() const {
	size_t result = sizeof(DDD::Group);
	for (auto e : *objects)
		result += e->size();
	return result;
}
