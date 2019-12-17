#pragma once
#ifndef _WIN64
#define _CATCH_ALL }catch(...){
#endif // !_CATCH_ALL

#include "renderable.h"
#include "../cgtools/point.h"
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
		void clear()noexcept;
		Hit intersect(Ray r)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		renderable* clone()const override;
		size_t size()const override;
	};
}
