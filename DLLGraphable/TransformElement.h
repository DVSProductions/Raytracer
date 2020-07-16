#pragma once
#include "GraphElement.h"
#include "../3DTools/Group.h"
#include "../cgtools/ATransformation.h"
#include "../cgtools/Translation.h"
namespace DDD {
	class TransformElement :public GraphElement {
		friend class GraphElement;
		std::unique_ptr<cgtools::ATransformation> transform;
		TransformElement(std::string serialized);
	public:
		static const int CLASSID = 1;
		TransformElement(std::unique_ptr<cgtools::ATransformation> myTransform);
		renderable* evaluate(uint64_t startSeed)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		size_t size()const noexcept override;
	};
}
