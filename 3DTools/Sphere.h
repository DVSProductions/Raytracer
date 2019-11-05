#pragma once
#include "Renderer.h"
#include "ISerializable.h"
#include "point.h"
#include "Scene.h"
namespace DDD {
	class Sphere :
		public renderable {
		double radius;
		double rsq;
		cgtools::Color c;
		friend class renderable;
		Sphere(std::string serialized);
	public:
		static const int CLASSID = 0;
		direction getNormal(point at) const noexcept;
		Sphere(cgtools::point position, double radius, cgtools::Color color) noexcept;
		Hit intersect(Ray r)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
	};

}

