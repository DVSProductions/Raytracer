#pragma once
#include "renderable.h"
#include "point.h"
#include <memory>
namespace DDD {
	class Plane :public renderable {
		double r = -1;
		cgtools::direction n;
		std::shared_ptr<AMaterial> Material;
		friend class renderable;
		Plane(std::string serialized);
	public:
		static const int CLASSID = 1;
		Plane(cgtools::point position, cgtools::direction dir, cgtools::Color color);
		Plane(cgtools::point position, cgtools::direction dir, cgtools::Color color, double radius);
		Plane(cgtools::point postion, cgtools::direction dir, std::shared_ptr<AMaterial> mat)noexcept;
		Plane(cgtools::point postion, cgtools::direction dir, std::shared_ptr<AMaterial> mat, double radius)noexcept;
		Hit intersect(Ray r)const noexcept override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		renderable* clone() const override;
		size_t size()const noexcept override;
	};
}
