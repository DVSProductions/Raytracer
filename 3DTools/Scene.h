#pragma once
#include <vector>
#include <renderable.h>
#include <memory>
namespace DDD {
	class Scene : public renderable {
		std::unique_ptr<std::vector<DDD::renderable*>> objects;
	public:
		Scene() noexcept;
		void addObject(DDD::renderable* obj);
		void clear();
		Hit* intersect(Ray r)const override;
		~Scene();
	};
}

