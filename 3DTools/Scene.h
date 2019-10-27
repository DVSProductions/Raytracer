#pragma once
#include <vector>
#include <renderable.h>
#include <memory>
namespace DDD {
	class Scene : public renderable {
	public:
		std::unique_ptr<std::vector <DDD::renderable*>> objects;
		Scene();
		void addObject(DDD::renderable* obj);
		Hit* intersect(Ray r) override;
	};
}

