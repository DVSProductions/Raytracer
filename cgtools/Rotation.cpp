#include "Rotation.h"
namespace cgtools {
	direction Rotation::axisToDirection(uint8_t caxis)noexcept {
		switch (caxis) {
		case 0:
			return direction(1, 0, 0);
		case 1:
			return direction(0, 1, 0);
		case 2:
			return direction(0, 0, 1);
		default:
			return direction(0, 0, 0);
		}
	}
	Rotation::Rotation(std::string str) : ComplexRotation(direction(0, 0, 0), 0) {
		load(str);
	}
	Rotation::Rotation(uint8_t axis, double angle)noexcept : ComplexRotation(axisToDirection(axis), angle) {}
	std::string Rotation::serialize() const {
		return includeClassID(std::to_string((int)axis) + "|" + std::to_string(angle), CLASSID);
	}
	void Rotation::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "|");
		f_chars(ret.at(0), axis);
		caxis = axisToDirection(axis);
		f_chars(ret.at(1), angle);
	}
	size_t Rotation::size() const {
		return sizeof(Rotation);
	}
}