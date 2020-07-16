#pragma once
#ifndef _WIN64
#define _CATCH_ALL }catch(...){
#endif // !_CATCH_ALL

#include "renderable.h"
#include "../cgtools/point.h"
#include "../cgtools/ATransformation.h"
//#include "../DLLGraphable/TransformElement.h"
#include <memory>
#include <vector>
#include <string>
namespace DDD {
	class Group : public renderable {
		friend class renderable;
		friend class TransformElement;
		static uint_fast64_t serializationIDs;
		Group(std::string serialized);
		Group()noexcept;
		Group(const Group& g);
		Group GroupClone();
		Group& operator=(const Group&) = default;
		cgtools::matrix transform;
		cgtools::matrix transformBack = !transform;
		cgtools::matrix transformTransposed = ~transformBack;
	protected:
		std::vector<DDD::renderable*> objects;
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
		void setTransform(cgtools::matrix EvaluatedTransform)noexcept;
	};
}
