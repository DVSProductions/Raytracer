#pragma once
#include "Hit.h"
#include "Material.h"
#include "Vanta.h"
#include "renderable.h"
namespace DDD {
	class Background : public renderable {
		std::shared_ptr<Vanta> Material;
		friend class renderable;
		friend class PinholeCamera;
		friend class MovablePinholeCamera;
		Background(std::string serialized);
	public:
		static const int CLASSID = -1;
		Background(cgtools::Color color);
		Hit intersect(Ray r)const noexcept override;
		std::string serialize()const override;
		std::string serializeFast()const;
		void load(std::string serialized) override;
		Background operator=(const Background& b)noexcept;
		renderable* clone() const override;
		size_t size()const noexcept override;
	};
}

