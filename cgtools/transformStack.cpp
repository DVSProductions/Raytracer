#include "transformStack.h"
namespace cgtools {
	transformStack::transformStack(std::string serialized){
		load(serialized);
	}
	matrix transformStack::operator()() noexcept {
		//if (children.size() == 0)return matrix();
		/*matrix m = (*children.at(0))();
		for (size_t n = 1; n < children.size(); n++)
			m *= (*children.at(n))();*/
		matrix m;
		const auto end = children.end(); 
		for (auto it = children.begin(); it != end; ++it) 
			//m *= it->get()->operator()();
			m *= (*(*it))();
		return m;
	}
	void transformStack::add(std::unique_ptr<ATransformation> t) noexcept {
		try {
			children.push_back(std::move(t));
		}
		catch (...) {}
	}
	std::string transformStack::serialize() const {
		std::string ret = "";
		const auto end = children.end();
		for (auto it = children.begin(); it != end; it++)
			ret += it->get()->serialize() + "{";
		return ret;
	}
	void transformStack::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "{");
		children.clear();
		for (auto s : ret) {
			auto ptr = ATransformation::createFromSerialization(s);
			if (ptr != nullptr) {
				children.push_back(std::move(ptr));
			}
		}
		
	}
	size_t transformStack::size() const {
		size_t total = sizeof(transformStack);
		const auto end = children.end();
		for (auto it = children.begin(); it != end; it++)
			total += it->get()->size();
		return total;
	}
	transformStack transformStack::clone() const noexcept {
		transformStack ret;
		const auto end = children.end();
		for (auto it = children.begin(); it != end; it++)
			ret.add(std::unique_ptr<ATransformation>(it->get()));
		return ret;
		return transformStack();
	}
}
