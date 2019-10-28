#include "Camera.h"

Camera::Camera(const point& pos, const double& angle)noexcept : position(pos.x,pos.y,pos.z) {
	this->angle = angle;
}

void Camera::setScene(std::shared_ptr<DDD::Scene> s)noexcept { scene=s; }

void Camera::move(const point& newPos)noexcept {
	position = newPos;
}

void Camera::setAngle(const double& newAngle)noexcept {
	angle = newAngle;
}
