#include "Glass.h"
namespace DDD {
	cgtools::direction Glass::refract(cgtools::direction d, cgtools::direction n, double n1, double n2) noexcept{
		const auto r = n1 / n2;
		const auto c = (-n)[d];
		return (d * r) + n * (r * c - sqrt(1 - (r * r) * (1 - c * c)));
	}

	double Glass::getSchlick(cgtools::direction d, cgtools::direction n, double n1, double n2) noexcept {
		const auto R02 = ((n1 - n2) / (n1 + n2));
		const auto R0 = R02 * R02;
		const auto p1 = (1 + n[d]);
		const auto p5 = p1 * p1 * p1 * p1 * p1;
		return R0 + (1 - R0) * p5;
	}
	Glass::Glass(std::string serialized) {
		load(serialized);
	}
	Glass::Glass(cgtools::Color Emi, cgtools::Color Albedo, double refractionIndex) noexcept {
		this->albedo = Albedo;
		this->emission = Emi;
		this->refractionIndex = refractionIndex;
		initRandom(0, 1);
	}
	cgtools::direction Glass::getScatteredDirection(Hit origin, Ray originalRay) {
		cgtools::direction localn = origin.n;
		double n1 = 1;
		double n2 = this->refractionIndex;
		if (localn[originalRay.dir] > 0) {
			localn = localn * -1.0;
			const double tmp = n1;
			n1 = n2;
			n2 = tmp;
		}
		const auto refr = refract(originalRay.dir,localn , n1, n2);
		if (refr.squaredLength() != 0 && dist() > getSchlick(originalRay.dir, localn, n1, n2))
			return refr;
		return originalRay.dir - 2 * (localn[originalRay.dir]) * localn;
	}
	Ray Glass::scatteredRay(Hit origin, Ray originalRay) {
		return Ray(origin.pos, getScatteredDirection(origin, originalRay), originalRay.tmax, 0.00001,this->refractionIndex);// Ray();
	}
	std::string Glass::serialize() const {
		return AMaterial::includeClassID(std::to_string(refractionIndex) + MaterialSplitter + albedo.serialize() + MaterialSplitter + emission.serialize() + MaterialSplitter, CLASSID);
	}
	void Glass::load(std::string serialized) {
		auto ret = Serializable::split(serialized, MaterialSplitter);
		f_chars(ret.at(0), refractionIndex);
		albedo.load(ret.at(1));
		emission.load(ret.at(2));
		initRandom(0,1);
	}
	AMaterial* Glass::clone() const {
		return new Glass(emission, albedo, refractionIndex);
	}
	size_t Glass::size() const noexcept {
		return sizeof(Glass);
	}
}