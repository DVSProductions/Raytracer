#pragma once
#include <vector>
#include "renderable.h"
#include <memory>
namespace DDD {
	class Scene : public renderable {
		std::unique_ptr<std::vector<DDD::renderable*>> objects;
	public:
		Scene() noexcept;
		~Scene();
		void addObject(DDD::renderable* obj);
		void clear();
		Hit intersect(Ray r)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		renderable* clone()const override;
		size_t size()const override;
	};
}

