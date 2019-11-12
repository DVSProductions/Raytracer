#include "Scene.h"

DDD::Scene::Scene()noexcept :renderable(cgtools::point(0, 0, 0)) {
	objects = std::make_unique <std::vector <DDD::renderable*>>();
}

void DDD::Scene::addObject(DDD::renderable* obj) {
	objects->push_back(obj);
}
void DDD::Scene::clear() {
	const auto end = objects->size();
	for (size_t n = 0; n != end; n++) 
		delete[](objects->at(n));
	objects->clear();
}
DDD::Hit DDD::Scene::intersect(DDD::Ray r)const {
	Hit closest;
	const auto end = objects->end();
	for (auto it = objects->begin(); it != end; it++) {
		const auto h = (*it)->intersect(r);
		if (h.hit && (!closest.hit || h.t < closest.t))
			closest = h;
	}
	return closest;
}

DDD::Scene::~Scene() {
	try {
		clear();
	}
	catch (...) {

	}
}

std::string DDD::Scene::serialize() const {
	const size_t siz = this->objects->size();
	std::string ret = "";
	for (size_t n = 0; n < siz; n++) {
		if (n != 0)ret += "$";
		ret += objects->at(n)->serialize();
	}
	return ret;
}
void DDD::Scene::load(std::string serialized) {
	auto ch = Serializable::split(serialized,"$");
	const size_t siz = ch.size();
	this->clear();
	for (size_t n = 0; n < siz; n++) {
		//printf("%d\n", n);
		objects->push_back(renderable::createFromSerialization(ch.at(n)));
	}
}

DDD::renderable* DDD::Scene::clone() const {
	auto ret = new Scene();
	const auto end = objects->end();
	for (auto it = objects->begin(); it != end; it++) 
		ret->addObject((*it)->clone());
	return ret;
}

size_t DDD::Scene::size() const {
	size_t result=sizeof(DDD::Scene);
	for (auto e : *objects) 
		result += e->size();
	return result;
}

