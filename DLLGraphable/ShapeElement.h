#pragma once
#include "graphElement.h"
namespace DDD {
	class ShapeElement :public GraphElement {
		renderable* child;
		friend class GraphElement;		
		ShapeElement(std::string serialized);
	public:
		static const int CLASSID = 2;
		ShapeElement(renderable* shape);
		renderable* evaluate(uint64_t startSeed)const override;
		std::string serialize()const override;
		void load(std::string serialized) override;
		size_t size()const noexcept override;
	};
}
