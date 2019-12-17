#pragma once
#include "../cgtools/Renderer.h"
#include "../cgtools/point.h"
#include "../cgtools/ISerializable.h"
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
		Sphere(cgtools::point position, double radius, cgtools::Color color);
		Sphere(cgtools::point position, double radius, std::shared_ptr<AMaterial> color) noexcept;
		Hit intersect(Ray r)const noexcept override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		renderable* clone() const override;
		size_t size()const noexcept override;
	};
}

