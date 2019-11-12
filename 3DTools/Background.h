#pragma once
#include <renderable.h>
#include <Hit.h>
#include "Material.h"
namespace DDD {
	class Background : public renderable {
		std::shared_ptr<Vanta> Material;
		friend class renderable;
		friend class PinholeCamera;
		Background(std::string serialized);
	public:
		static const int CLASSID = -1;
		Background(cgtools::Color color)noexcept;
		Hit intersect(Ray r)const override;
		std::string serialize()const override;
		std::string serializeFast()const;
		void load(std::string serialized) override;
		Background operator=(const Background& b)noexcept;
		renderable* clone() const;
		size_t size()const override;
	};
}

