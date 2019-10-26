#include "Scene.h"

DDD::Scene::Scene():renderable(cgtools::point(0,0,0)) {}

void DDD::Scene::addObject(DDD::renderable* obj) {
	objects.push_back(obj);
}

DDD::Hit* DDD::Scene::intersect(DDD::Ray r) {
	Hit* closest=nullptr;
	const auto end = objects.end();
	for (auto it = objects.begin(); it != end; it++) {
		const auto h = (*it)->intersect(r);
		if (h != nullptr && (closest == nullptr || h->t < closest->t))
			closest = h;
	}
	return closest;
}
