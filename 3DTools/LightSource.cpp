#include "LightSource.h"
namespace DDD {
	LightSource::LightSource(std::string serialized) :Vanta(cgtools::Color(0, 0, 0)) {
		load(serialized);
	}
	LightSource::LightSource(cgtools::Color Emission, double overdrive)noexcept : Vanta(Emission* overdrive) {}
	std::string LightSource::serialize() const {
		return AMaterial::includeClassID(emission.serialize(), CLASSID);
	}
	void LightSource::load(std::string serialized) {
		emission.load(serialized);
	}
	AMaterial* LightSource::clone() const {
		return new LightSource(emission, 1);
	}
}