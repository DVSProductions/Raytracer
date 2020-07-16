#pragma once
#include "graphElement.h"
#include "../3DTools/Scene.h"
#include <vector>
namespace DDD {
	class GraphRoot : public GraphElement {
		friend class GraphElement;
		GraphRoot(std::string serialized);
	public:
		static const int CLASSID = 3;
		// Geerbt über GraphElement
		std::string serialize() const override;
		void load(std::string serialized) override;
		size_t size() const override;
		renderable* evaluate(uint64_t startSeed)const override;
		Scene evaluateReal(uint64_t startSeed)const;
		static std::shared_ptr<GraphRoot> generateTree(std::string fullGraph);
	};
}
