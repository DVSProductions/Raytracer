#include "ShapeElement.h"
namespace DDD {
	ShapeElement::ShapeElement(std::string serialized) {
		load(serialized);
	}
	ShapeElement::ShapeElement(renderable* shape) {
		child = shape;
	}
	renderable* ShapeElement::evaluate(uint64_t startSeed)const {
		return child->clone();
	}
	std::string ShapeElement::serialize() const {
		return includeClassID(child->serialize(),CLASSID);
	}
	void ShapeElement::load(std::string serialized) {
		child = renderable::createFromSerialization(serialized);
	}
	size_t ShapeElement::size() const noexcept {
		return sizeof(ShapeElement) + child->size();
	}
}