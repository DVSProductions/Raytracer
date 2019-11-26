#pragma once
#include "Mirror.h"
namespace DDD {
	class Metal : public Mirror {
		friend class AMaterial;
		static const int CLASSID = 4;
		Metal(std::string serialized);
	public:
		Metal(cgtools::Color Emi, cgtools::Color Albedo, double roughness) noexcept;
		Ray scatteredRay(Hit origin, Ray originalRay)noexcept override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const override;
	};
}

