#include "renderable.h"
namespace DDD {
	renderable::renderable(cgtools::point position)noexcept :p(position) {}
	renderable::renderable(std::string serialized) :p(0,0,0) {
		p.load(serialized);
	}
	renderable* renderable::createFromSerialization(std::string data) {
		return nullptr;
	}
}
