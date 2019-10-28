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
DDD::Hit* DDD::Scene::intersect(DDD::Ray r)const {
	Hit* closest = nullptr;
	const auto end = objects->end();
	for (auto it = objects->begin(); it != end; it++) {
		const auto h = (*it)->intersect(r);
		if (h != nullptr && (closest == nullptr || h->t < closest->t))
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

