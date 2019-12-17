#pragma once
#include "renderable.h"
#include "../cgtools/point.h"
namespace DDD {
	class Pipe : public renderable {
		double radius, height, rsq;
		std::shared_ptr<AMaterial> material;
		friend class renderable;
		Pipe(std::string serialized);
		static const int CLASSID = 3;
	public:
		Pipe(cgtools::point position, double radius, double height, std::shared_ptr<AMaterial> mat);
		Hit intersect(Ray r)const noexcept override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		renderable* clone() const override;
		size_t size()const noexcept override;	
	};
}
