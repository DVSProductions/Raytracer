#include "Translation.h"
namespace cgtools {
	Translation::Translation(std::string str):offset(direction(0,0,0)) {
		load(str);
	}
	Translation::Translation(vector offset)noexcept :offset(offset) {}
	matrix Translation::operator()()const noexcept {
		return matrix::createTranslation(offset);
	}
	std::string Translation::serialize() const {
		return includeClassID(offset.serialize(),CLASSID);
	}
	void Translation::load(std::string serialized) {
		offset.load(serialized);
	}
	size_t Translation::size() const {
		return sizeof(Translation);
	}
	vector Translation::getOffset() const noexcept{
		return offset;
	}
}