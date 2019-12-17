#include "transformStack.h"
namespace cgtools {
	matrix transformStack::operator()() noexcept {
		if (children.size() == 0)return matrix();
		/*matrix m = (*children.at(0))();
		for (size_t n = 1; n < children.size(); n++)
			m *= (*children.at(n))();*/
		matrix m;
		for (auto e : children)
			m *= (*e)();
		return m;
	}
	void transformStack::add(ATransformation* t) {
		children.push_back(t);
	}
	std::string transformStack::serialize() const {
		std::string ret = "";
		for (auto e : children)
			ret += e->serialize() + "{";
		return ret;
	}
	void transformStack::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "{");
		children.clear();
		for (auto s : ret)
			children.push_back(ATransformation::createFromSerialization(s));
	}
	size_t transformStack::size() const {
		size_t total = sizeof(transformStack);
		for (auto t : children)
			total += t->size();
		return total;
	}
	transformStack transformStack::clone() const noexcept {
		transformStack ret;
		for (auto t : children)ret.add(t);
		return ret;
	}
}
