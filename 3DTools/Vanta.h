#pragma once

#include "Material.h"
namespace DDD {
	class Vanta :public AMaterial {
		friend class AMaterial;
		static const int CLASSID = 0;
		Vanta(std::string serialized);
	public:
		Vanta(cgtools::Color Material)noexcept;
		Ray scatteredRay(Hit origin, Ray originalRay)override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const override;
		size_t size()const noexcept override;
	};
}