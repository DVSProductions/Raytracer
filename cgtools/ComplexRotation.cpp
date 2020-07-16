#include "ComplexRotation.h"
namespace cgtools {
	ComplexRotation::ComplexRotation(std::string str):caxis(0,0,0) {
		load(str);
	}

	ComplexRotation::ComplexRotation(direction axis, double angle) noexcept:caxis(axis),angle(angle) {}

	matrix ComplexRotation::operator()() const noexcept {
		return matrix::createRotation(caxis, angle);
	}

	std::string ComplexRotation::serialize() const {
		return includeClassID(caxis.serialize() + ";" + std::to_string(angle)+";", CLASSID);
	}
	void ComplexRotation::load(std::string serialized) {
		auto ret = Serializable::split(serialized, ";");
		caxis.load(ret.at(0));
		f_chars(ret.at(1), angle);
	}

	size_t ComplexRotation::size() const {
		return sizeof(ComplexRotation);
	}
}