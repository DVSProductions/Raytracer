#include "Rotation.h"
namespace cgtools {
	//direction Rotation::axisToDirection(int16_t axis)noexcept {
	//	switch (axis) {
	//	case 0:
	//		return direction(1, 0, 0);
	//	case 1:
	//		return direction(0, 1, 0);
	//	case 2:
	//		return direction(0, 0, 1);
	//	default:
	//		return direction(0, 0, 0);
	//	}
	//}
	Rotation::Rotation(std::string str){
		load(str);
	}
	Rotation::Rotation(Axis axis, double angle)noexcept {
		this->axis = axis;
		this->angle = angle;
	}
	matrix Rotation::operator()() const noexcept {
		switch (axis) {
		case(Axis::y):
			return matrix::createRotationY(angle);
		case(Axis::z):
			return matrix::createRotationZ(angle);
		default:
			return matrix::createRotationX(angle);
		}
	}
	std::string Rotation::serialize() const {
		return includeClassID(std::to_string((int)axis) + "|" + std::to_string(angle), CLASSID);
	}
	void Rotation::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "|");
		int16_t axisV = 0;
		f_chars(ret.at(0), axisV);
		axis = static_cast<Axis>(axisV);
		f_chars(ret.at(1), angle);
	}
	size_t Rotation::size() const {
		return sizeof(Rotation);
	}
}