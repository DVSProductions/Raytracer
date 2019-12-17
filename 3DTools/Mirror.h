#pragma once
#include "Material.h"
namespace DDD {
	class Mirror :public  AMaterial {
		friend class AMaterial;
		static const int CLASSID = 1;
		Mirror(std::string serialized);
	
	public:
		Mirror(cgtools::Color Material) noexcept;
		Mirror(cgtools::Color Emi, cgtools::Color Albe) noexcept;
		Ray scatteredRay(Hit origin, Ray originalRay) noexcept override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const override;
		size_t size()const noexcept override;
	};
}