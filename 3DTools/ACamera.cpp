#include "ACamera.h"
#include "PinholeCamera.h"
#define deserial(c,val) case c::CLASSID: return std::make_shared<c>(c(val))
DDD::ACamera::ACamera(const point& pos, const double& angle)noexcept : position(pos.x, pos.y, pos.z) {
	this->angle = angle;
}

std::string DDD::ACamera::includeClassID(std::string data, int CID) {
	return std::to_string(CID) + "!" + data;
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
#include <stdexcept>
std::shared_ptr<DDD::ACamera> DDD::ACamera::createFromSerialization(std::string data) {
	const auto s = Serializable::split(data, "!");
	int n = -1;
	f_chars(s.at(0), n);
	switch (n) {
		deserial(DDD::PinholeCamera, s.at(1));
	}
	throw std::invalid_argument("Unknown type :" + s.at(0));
}
