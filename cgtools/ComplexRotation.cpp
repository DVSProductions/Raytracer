#include "ComplexRotation.h"
namespace cgtools {
	cgtools::ComplexRotation::ComplexRotation(std::string str):caxis(0,0,0) {
		load(str);
	}

	cgtools::ComplexRotation::ComplexRotation(direction axis, double angle) noexcept:caxis(axis),angle(angle) {}

	matrix cgtools::ComplexRotation::operator()() const noexcept {
		return matrix::createRotation(caxis, angle);
	}

	std::string cgtools::ComplexRotation::serialize() const {
		return includeClassID(caxis.serialize() + ";" + std::to_string(angle)+";", CLASSID);
	}
	void cgtools::ComplexRotation::load(std::string serialized) {
		auto ret = Serializable::split(serialized, ";");
		caxis.load(ret.at(0));
		f_chars(ret.at(1), angle);
	}

	size_t cgtools::ComplexRotation::size() const {
		return sizeof(ComplexRotation);
	}
}