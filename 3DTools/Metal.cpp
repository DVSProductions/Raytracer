#include "Metal.h"
namespace DDD {
	Metal::Metal(std::string serialized) :Mirror(cgtools::Color(0, 0, 0), cgtools::Color(0, 0, 0)) {
		load(serialized);
	}
	Metal::Metal(cgtools::Color Emi, cgtools::Color Albedo, double roughness) noexcept : Mirror(Emi, Albedo) {
		scatterFactor = roughness;
		initRandom(scatterFactor);
	}
	Ray Metal::scatteredRay(Hit origin, Ray originalRay)  noexcept {
		const auto r = ~((originalRay.dir - 2 * (origin.n[originalRay.dir]) * origin.n) + cgtools::direction(RNG(), RNG(), RNG()));
		return Ray(origin.pos, r, originalRay.tmax, 0.000001);
	}
	std::string Metal::serialize() const {
		return AMaterial::includeClassID(std::to_string(scatterFactor) + MaterialSplitter + albedo.serialize() + MaterialSplitter + emission.serialize() + MaterialSplitter, CLASSID);
	}
	void Metal::load(std::string serialized) {
		auto ret = Serializable::split(serialized, MaterialSplitter);
		f_chars(ret.at(0), scatterFactor);
		albedo.load(ret.at(1));
		emission.load(ret.at(2));
		initRandom(scatterFactor);
	}
	AMaterial* Metal::clone() const {
		return new Metal(emission, albedo, scatterFactor);
	}
}