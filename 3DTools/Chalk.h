#pragma once
#include "Material.h"
namespace DDD{
	class Chalk :public AMaterial {
		friend class AMaterial;
		static const int CLASSID = 2;
		Chalk(std::string serialized);
	public:
		Chalk(cgtools::Color Emi, cgtools::Color alb) noexcept;
		Ray scatteredRay(Hit origin, Ray originalRay)override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const override;
		size_t size()const noexcept override;
	};
}