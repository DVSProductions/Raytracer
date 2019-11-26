#include "Mirror.h"
namespace DDD {
	Mirror::Mirror(std::string serialized) {
		scatterFactor = 0;
		load(serialized);
	}
	Mirror::Mirror(cgtools::Color Material) noexcept {
		scatterFactor = 0;
		emission = Material;
		albedo = cgtools::c_white;
	}
	Mirror::Mirror(cgtools::Color Emi, cgtools::Color Albe) noexcept {
		scatterFactor = 0;
		emission = Emi;
		albedo = Albe;
	}
	Ray Mirror::scatteredRay(Hit origin, Ray originalRay) noexcept {
		const auto r = originalRay.dir - 2 * (origin.n[originalRay.dir]) * origin.n;
		return Ray(origin.pos, r, originalRay.tmax, 0.000001);
	}
	std::string Mirror::serialize() const {
		return AMaterial::includeClassID(albedo.serialize() + MaterialSplitter + emission.serialize() + MaterialSplitter, CLASSID);
	}
	void Mirror::load(std::string serialized) {
		auto ret = Serializable::split(serialized, MaterialSplitter);
		albedo.load(ret.at(0));
		emission.load(ret.at(1));
	}
	AMaterial* Mirror::clone() const {
		return new Mirror(emission, albedo);
	}
	size_t Mirror::size() const noexcept {
		return sizeof(Mirror);
	}
}