#pragma once
#include "renderable.h"
#include "point.h"
#include <memory>
#include <vector>
#include <string>
namespace DDD {
	class Group : public renderable {
		std::unique_ptr<std::vector<DDD::renderable*>> objects;
		friend class renderable;
		Group(std::string serialized);
	public:
		static const int CLASSID = 2;
		Group(cgtools::point position); 
		~Group();
		void addObject(DDD::renderable* obj);
		void clear();
		Hit intersect(Ray r)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		renderable* clone()const override;
		size_t size()const override;
	};
}
