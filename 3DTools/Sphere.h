#pragma once
#include "Renderer.h"
#include "ISerializable.h"
#include "point.h"
#include "Scene.h"
#include "Material.h"
namespace DDD {
	class Sphere :
		public renderable {
		double radius;
		double rsq;
		std::shared_ptr<AMaterial>  material;
		friend class renderable;
		Sphere(std::string serialized);
		static const int CLASSID = 0;
	public:
		cgtools::direction getNormal(cgtools::point at) const noexcept;
		Sphere(cgtools::point position, double radius, cgtools::Color color) noexcept;
		Sphere(cgtools::point position, double radius, std::shared_ptr<AMaterial>  color) noexcept;
		Hit intersect(Ray r)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		renderable* clone() const;
		size_t size()const override;
	};

}

