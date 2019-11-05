#pragma once
#include "renderable.h"
#include "point.h"
namespace DDD {
	class Plane :public renderable {
		double r = -1;
		cgtools::direction n;
		cgtools::Color c;
		friend class renderable;
		Plane(std::string serialized);
	public:
		static const int CLASSID = 1;
		Plane(cgtools::point position, cgtools::direction dir, cgtools::Color color) noexcept;
		Plane(cgtools::point position, cgtools::direction dir, cgtools::Color color, double radius) noexcept;
		Hit intersect(Ray r)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
	};
}
