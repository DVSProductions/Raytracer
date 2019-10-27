#include "Camera.h"

Camera::Camera(const point& pos, const double& angle): position(pos.x,pos.y,pos.z) {
	this->angle = angle;
}

void Camera::setScene(std::shared_ptr<DDD::Scene> s) { scene=s; }
