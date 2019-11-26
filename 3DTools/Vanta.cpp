#include "Vanta.h"
namespace DDD {
	Vanta::Vanta(std::string serialized) {
		load(serialized);
	}

	Vanta::Vanta(cgtools::Color Material)noexcept {
		scatterFactor = 0;
		emission = Material;
		albedo = cgtools::c_black;
	}
	Ray Vanta::scatteredRay(Hit origin, Ray originalRay) {
		throw std::logic_error("Vanta Fully absorbes Rays!");
	}
	std::string Vanta::serialize() const {
		return AMaterial::includeClassID(emission.serialize(), CLASSID);
	}
	void Vanta::load(std::string serialized) {
		/// <summary>
		/// ensure compatablility with colors
		/// </summary>
		/// <param name="serialized"></param>
		scatterFactor = 0;
		emission.load(serialized);
		albedo = cgtools::c_black;
	}
	AMaterial* Vanta::clone() const {
		return new Vanta(emission);
	}
	size_t Vanta::size() const noexcept {
		return sizeof(Vanta);
	}
}