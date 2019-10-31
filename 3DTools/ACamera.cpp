#include "ACamera.h"
DDD::ACamera::ACamera(const point& pos, const double& angle)noexcept : position(pos.x, pos.y, pos.z) {
	this->angle = angle;
}

void DDD::ACamera::setScene(std::shared_ptr<DDD::Scene> s)noexcept { scene = s; }

void DDD::ACamera::move(const point& newPos)noexcept {
	position = newPos;
}

void DDD::ACamera::setAngle(const double& newAngle)noexcept {
	angle = newAngle;
}

std::string DDD::ACamera::serialize()const {
	return std::to_string(this->angle) + "&" + position.serialize();
}

void DDD::ACamera::load(std::string serialized) {
	auto ret = Serializable::split(serialized, "&");
	f_chars(ret[0], angle);
	position.load(ret[1]);
}
