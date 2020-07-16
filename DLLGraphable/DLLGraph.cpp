#include "DLLGraph.h"
#include "GraphRoot.h"
#include "../3DDLL/3DInfo.h"
EXTERN_C_START
dll(int) GetSupportedGeneratorsAt(int idx) {
	if (idx < 0)return -1;
	return supportedGenerators[idx];
}
dll(void) ImportTree(const char* serializedData) {
	if (SceneGraph != nullptr)
		SceneGraph.reset();
	SceneGraph = DDD::GraphRoot::generateTree(std::string(serializedData));
}
dll(void) EvaluateGraph(uint64_t seed) {
	playground->clear();
	auto v2 = std::make_shared <DDD::Scene>(SceneGraph->evaluateReal(seed));
	playground.swap(v2);
}
EXTERN_C_END