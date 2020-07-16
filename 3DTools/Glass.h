#pragma once
#include "Material.h"
namespace DDD {
	class Glass : public AMaterial {
		friend class AMaterial;
		static const int CLASSID = 5;
		double refractionIndex = 0;
		Glass(std::string serialized);
		static cgtools::direction refract(cgtools::direction d, cgtools::direction n, double n1, double n2)noexcept;
		static double getSchlick(cgtools::direction d, cgtools::direction n, double n1, double n2)noexcept;
	public:
		Glass(cgtools::Color Emi, cgtools::Color Albedo, double refractionIndex) noexcept;
		cgtools::direction getScatteredDirection(Hit origin, Ray originalRay) noexcept;
		Ray scatteredRay(Hit origin, Ray originalRay)override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const override;
		size_t size()const noexcept override;
	};
}