#include "Chalk.h"
namespace DDD {
	Chalk::Chalk(std::string serialized) {
		scatterFactor = 1;
		load(serialized);
	}
	Chalk::Chalk(cgtools::Color Emi, cgtools::Color alb) noexcept {
		scatterFactor = 1;
		initRandom(scatterFactor);
		albedo = alb;
		emission = Emi;
	}
	Ray Chalk::scatteredRay(Hit origin, Ray originalRay) {
		auto r = cgtools::direction(RNG(), RNG(), RNG());
		while (r.squaredLength() > 1) {
			r = cgtools::direction(RNG(), RNG(), RNG());
		}
		return Ray(origin.pos, ~(r + origin.n), originalRay.tmax, 0.000001);
		//return Ray(origin.pos, ~(cgtools::direction(RNG(), RNG(), RNG()) + origin.n), originalRay.tmax, 0.000001);
	}
	std::string Chalk::serialize() const {
		return AMaterial::includeClassID(albedo.serialize() + MaterialSplitter + emission.serialize() + MaterialSplitter, CLASSID);
	}
	void Chalk::load(std::string serialized) {
		auto ret = Serializable::split(serialized, MaterialSplitter);
		albedo.load(ret.at(0));
		emission.load(ret.at(1));
		initRandom(scatterFactor);
	}
	AMaterial* Chalk::clone() const {
		return new Chalk(emission, albedo);
	}
	size_t Chalk::size() const noexcept {
		return sizeof(Chalk);
	}
}