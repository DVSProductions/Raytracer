#include "Camera.h"

Camera::Camera(const cgtools::point& pos, const double& angle)noexcept : position(pos.x,pos.y,pos.z) {
	this->angle = angle;
}

void Camera::setScene(std::shared_ptr<DDD::Scene> s)noexcept { 
	scene=s;
}

void Camera::move(const cgtools::point& newPos)noexcept {
	position = newPos;
}

void Camera::setAngle(const double& newAngle)noexcept {
	angle = newAngle;
}

std::string Camera::serialize()const {
	return std::to_string(this->angle) + "&" + position.serialize();
}

void Camera::load(std::string serialized) {
	auto ret=Serializable::split(serialized, "&");
	f_chars(ret[0], angle);
	position.load(ret[1]);
}
