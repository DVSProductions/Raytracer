#pragma once
#include "Vanta.h"
namespace DDD {
	class LightSource : public Vanta {
		friend class AMaterial;
		static const int CLASSID = 3;
		LightSource(std::string serialized);
	public:
		LightSource(cgtools::Color Emission, double overdrive) noexcept;
		std::string serialize()const override;
		void load(std::string serialized) override;
		AMaterial* clone() const override;
	};
}

