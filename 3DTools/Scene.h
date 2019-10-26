#pragma once
#include <vector>
#include <renderable.h>
namespace DDD {
	class Scene : public renderable {
		std::vector <DDD::renderable*> objects;

	public:
		Scene();
		void addObject(DDD::renderable* obj);
		Hit* intersect(Ray r) override;
	};
}

