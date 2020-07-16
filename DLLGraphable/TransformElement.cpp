#include "TransformElement.h"
namespace DDD {
	TransformElement::TransformElement(std::string serialized) {
		load(serialized);
	}
	TransformElement::TransformElement(std::unique_ptr<cgtools::ATransformation> myTransform) {
		transform.swap(myTransform);
	}

	renderable* TransformElement::evaluate(uint64_t startSeed)const {
		auto ret = new Group();
		ret->setTransform((*transform)());
		for (auto& e : children)
			ret->addObject(e->evaluate(startSeed++));
		return ret;
		return nullptr;
	}

	std::string TransformElement::serialize() const {
		return includeClassID(transform->serialize(), CLASSID);
	}
	void TransformElement::load(std::string serialized) {
		transform = std::move(cgtools::ATransformation::createFromSerialization(serialized));
	}

	size_t TransformElement::size() const noexcept {
		return sizeof(TransformElement);
	}
}