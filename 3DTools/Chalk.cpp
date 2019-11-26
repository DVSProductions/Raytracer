#include "Chalk.h"
namespace DDD {
	Chalk::Chalk(std::string serialized) {
		scatterFactor = 1;
		load(serialized);
	}
	Chalk::Chalk(cgtools::Color Emi, cgtools::Color alb) noexcept {
		scatterFactor = 1;
		dist = cxx::ziggurat_normal_distribution<double>(0, scatterFactor / 2);
		albedo = alb;
		emission = Emi;
	}
	Ray Chalk::scatteredRay(Hit origin, Ray originalRay) {
		cgtools::direction r = cgtools::direction(dist(mt), dist(mt), dist(mt));
		while (r.squaredLength() > 1) {
			r = cgtools::direction(dist(mt), dist(mt), dist(mt));
		}
		return Ray(origin.pos, ~(r + origin.n), originalRay.tmax, 0.000001);
		//return Ray(origin.pos, ~(cgtools::direction(dist(mt), dist(mt), dist(mt)) + origin.n), originalRay.tmax, 0.000001);
	}
	std::string Chalk::serialize() const {
		return AMaterial::includeClassID(albedo.serialize() + MaterialSplitter + emission.serialize() + MaterialSplitter, CLASSID);
	}
	void Chalk::load(std::string serialized) {
		auto ret = Serializable::split(serialized, MaterialSplitter);
		albedo.load(ret.at(0));
		emission.load(ret.at(1));
	}
	AMaterial* Chalk::clone() const {
		return new Chalk(emission, albedo);
	}
	size_t Chalk::size() const noexcept {
		return sizeof(Chalk);
	}
}