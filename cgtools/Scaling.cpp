#include "Scaling.h"
namespace cgtools {
	Scaling::Scaling(std::string str) :factors(point(0,0,0)){
		load(str);
	}
	Scaling::Scaling(vector factors)noexcept :factors(factors) {}
	matrix Scaling::operator()() const noexcept {
		return matrix::createScaler(this->factors);
	}
	std::string Scaling::serialize() const {
		return includeClassID(factors.serialize(),CLASSID);
	}
	void Scaling::load(std::string serialized) {
		factors.load(serialized);
	}
	size_t Scaling::size() const {
		return sizeof(Scaling);
	}
}