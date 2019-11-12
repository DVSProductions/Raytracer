#include <Windows.h>
#include "CppUnitTest.h"
#include "../cgtools/Color.h"
#include "../Aufgabe5/Aufgabe5.cpp"

#include <bitset>
#include <sstream>
//using std::cout; using std::endl;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
std::string names[] = { "ProcessorCore", "NumaNode", "Cache", "ProcessorPackage","Group" };
void setCamera(const char* serializedData) {
	auto sh = DDD::ACamera::createFromSerialization(std::string(serializedData));
	if (cam != nullptr) {
		cam.reset();
		cam.swap(sh);
	}
	else
		cam = sh;
	cam->setScene(playground);
}
namespace My3DTest {

	TEST_CLASS(My3DTest) {
	public:
		void printInfo(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX c, int idx) {
			std::stringstream s;
			s << "Entry [" << idx << "]"
				<< "\n\tRelationship: " << names[c->Relationship];
			if (c->Relationship == _LOGICAL_PROCESSOR_RELATIONSHIP::RelationCache)
				s
				<< "\n\t\tAssociativity: " << std::bitset<8>(c->Cache.Associativity)
				<< "\n\t\tCacheSize: " << c->Cache.CacheSize
				<< "\n\t\tGroupMask.Group: " << c->Cache.GroupMask.Group
				<< "\n\t\tGroupMask.Mask: " << std::bitset<64>(c->Cache.GroupMask.Mask)
				<< "\n\t\tGroupMask.Reserved: " << c->Cache.GroupMask.Reserved
				<< "\n\t\tLevel: " << (int)c->Cache.Level
				<< "\n\t\tLineSize: " << c->Cache.LineSize
				<< "\n\t\tReserved: " << c->Cache.Reserved
				<< "\n\t\tType: " << c->Cache.Type;
			else if (c->Relationship == _LOGICAL_PROCESSOR_RELATIONSHIP::RelationGroup)
				s
				<< "\n\t\tActiveGroupCount: " << c->Group.ActiveGroupCount
				<< "\n\t\tGroupInfo->ActiveProcessorCount: " << (int)c->Group.GroupInfo->ActiveProcessorCount
				<< "\n\t\tGroupInfo->ActiveProcessorMask: " << std::bitset<64>(c->Group.GroupInfo->ActiveProcessorMask)
				<< "\n\t\tGroupInfo->MaximumProcessorCount: " << (int)c->Group.GroupInfo->MaximumProcessorCount
				<< "\n\t\tGroupInfo->Reserved: " << c->Group.GroupInfo->Reserved
				<< "\n\t\tMaximumGroupCount: " << c->Group.MaximumGroupCount
				<< "\n\t\tReserved: " << c->Group.Reserved;
			else if (c->Relationship == _LOGICAL_PROCESSOR_RELATIONSHIP::RelationNumaNode)
				s
				<< "\n\t\tGroupMask.Group: " << c->NumaNode.GroupMask.Group
				<< "\n\t\tGroupMask.Mask: " << std::bitset<64>(c->NumaNode.GroupMask.Mask)
				<< "\n\t\tGroupMask.Reserved: " << c->NumaNode.GroupMask.Reserved
				<< "\n\t\tNodeNumber: " << c->NumaNode.NodeNumber
				<< "\n\t\tReserved: " << c->NumaNode.Reserved;
			else if (c->Relationship == _LOGICAL_PROCESSOR_RELATIONSHIP::RelationProcessorCore)
				s << "--------------------------------------------\n"
				<< "\n\t\tEfficiencyClass: " << (int)c->Processor.EfficiencyClass
				<< "\n\t\tFlags: " << (int)c->Processor.Flags
				<< "\n\t\tGroupCount: " << c->Processor.GroupCount
				<< "\n\t\tGroupMask->Group: " << c->Processor.GroupMask->Group
				<< "\n\t\tGroupMask->Mask: " << std::bitset<64>(c->Processor.GroupMask->Mask)
				<< "\n\t\tGroupMask->Reserved: " << c->Processor.GroupMask->Reserved
				<< "\n\t\tReserved: " << c->Processor.Reserved;
			s << "\n" << "\n" << "\n";
			OutputDebugStringA(s.str().c_str());
		}
		TEST_METHOD(ChacheCow_GetInfo) {
			/*CacheCow cc;
			cc.init();
			auto fullInfo = CreateGroups();
			for (auto g : fullInfo) {
				OutputDebugStringA(g.toString(0).c_str());
			}*/
			return;
		}
		std::string cam = "0!0.25|0.25|0.25|[1.5707963267949&0|0|0|&4&[!";
		std::string scene = "0!1&2!0.9|0.9|0.9|}0.5|0.5|0.5|}!&0|0|-3|&!$1!-1&0|1|0|&2!0.9|0.9|0.9|}0.5|0.5|0.5|}!&0|-3|0|&!$"; 
		std::string scen2 = "0!1&2#0.9|0.9|0.9|}0.5|0.5|0.5|}#&0|0|-3|&!$1!-1&0|1|0|&2#0.9|0.9|0.9|}0.5|0.5|0.5|}#&0|-3|0|&!$"; 
		TEST_METHOD(RaytracingTest) {
			prepare3d();
			playground->load(scen2);
			setCamera(cam.c_str());
			renderPreview(160, 90);
		}
	};
}
