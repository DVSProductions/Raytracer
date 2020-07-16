#include "GraphRoot.h"
#include "../cgtools/ISerializable.h"
#include <memory>
#include "../3DTools/Scene.h"
namespace DDD {
	GraphRoot::GraphRoot(std::string serialized) {
		load(serialized);
	}
	std::shared_ptr<GraphRoot> GraphRoot::generateTree(std::string fullGraph) {
		std::vector<GraphElement*> memory;
		const auto mem = Serializable::split(fullGraph, "(");
		for (auto& e : mem) {
			auto elem = GraphElement::createFromSerialization(e);
			while (elem->address > memory.size())
				memory.push_back(nullptr);
			memory[elem->address] = elem;
		}
		const auto treeDefinition = Serializable::split(fullGraph, ")");
		const auto siz = treeDefinition.size();
		for (size_t n = 1; n < siz; n++) {
			const auto linkage = Serializable::split(treeDefinition.at(n), "~");
			const auto count = linkage.size();
			uint64_t tmp = 0, target = 0;
			f_chars(linkage.at(0), target);
			if (memory[target] != nullptr)
				for (size_t i = 1; i < count; i++) {
					f_chars(linkage.at(i), tmp);
					if (memory[tmp] != nullptr)
						memory[target]->children.push_back(memory[tmp]);
				}
		}
		for (auto cell : memory)
			if (cell != nullptr && typeid(*cell) == typeid(GraphRoot))
				return std::shared_ptr<GraphRoot>((GraphRoot*)cell);
		return nullptr;
	}
	std::string GraphRoot::serialize() const {
		return includeClassID("", CLASSID);
	}
	void GraphRoot::load(std::string serialized) {
	}
	size_t GraphRoot::size() const {
		return sizeof(GraphRoot);
	}
	renderable* GraphRoot::evaluate(uint64_t startSeed) const{
		//static_assert (false, "Do not use!");
		return nullptr;
	}
	Scene GraphRoot::evaluateReal(uint64_t startSeed)const {
		Scene g;
		for (auto& c : children)
			g.addObject(c->evaluate(++startSeed));
		return g;
	}
}