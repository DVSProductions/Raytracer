#include "ACamera.h"
#include "PinholeCamera.h"
#include "MovablePinholeCamera.h"
#define deserial(cam) case cam::CLASSID: return std::make_shared<cam>(cam(s.at(1)))

DDD::ACamera::ACamera(const double& angle) noexcept : position(0, 0, 0) {
	this->angle = angle;
}

DDD::ACamera::ACamera(const cgtools::point& pos, const double& angle)noexcept : position(pos.x, pos.y, pos.z) {
	this->angle = angle;
}

DDD::ACamera::~ACamera() noexcept {
	this->scene.reset();
}

std::string DDD::ACamera::includeClassID(std::string data, int CID) {
	return std::to_string(CID) + "!" + data;
}

void DDD::ACamera::setScene(std::shared_ptr<DDD::Scene> s)noexcept { scene = s; }

void DDD::ACamera::move(const cgtools::point& newPos)noexcept {
	position = newPos;
}

void DDD::ACamera::setAngle(const double& newAngle)noexcept {
	angle = newAngle;
}

std::string DDD::ACamera::serialize()const {
	return std::to_string(this->angle) + "&" + position.serialize() + "&" + std::to_string(reflectionDepth);
}

void DDD::ACamera::load(std::string serialized) {
	auto ret = Serializable::split(serialized, "&");
	f_chars(ret.at(0), angle);
	position.load(ret.at(1));
	if (ret.size() == 3)
		f_chars(ret.at(2), reflectionDepth);
}
#include <stdexcept>
std::shared_ptr<DDD::ACamera> DDD::ACamera::createFromSerialization(std::string data) {
	const auto s = Serializable::split(data, "!");
	int n = -1;
	f_chars(s.at(0), n);
	switch (n) {
		deserial(DDD::PinholeCamera);
		deserial(DDD::MovablePinholeCamera);
	}
	throw std::invalid_argument("Unknown type :" + s.at(0));
}

size_t DDD::ACamera::size() const {
	return sizeof(DDD::ACamera) + scene->size();
}
