#define _USE_MATH_DEFINES 
#include "Aufgabe4.cpp"
#include "../3DTools/Plane.h"
#include "../3DTools/renderable.h"
#include "../3DTools/Background.h"
#include "../3DTools/Group.h"
#include "CppUnitTest.h"
#define dll(x) __declspec(dllexport) x __cdecl
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace cgtools;
using namespace DDD;

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
namespace A4Tester {
	TEST_CLASS(A4Tester) {
public:
	std::string scene = "0!1&0.5|0.5|0.5|&0|0|-3|&!$";
	std::string camera = "0!0.25|0.25|0.25|[1.5707963267949&0|0|0|&[!";
	TEST_METHOD(TestMethod1) {
		prepare3d();
		playground->load(scene);
		setCamera(camera.c_str());
		renderPreview(160, 90);
	}
	TEST_METHOD(Test2) {
		width = 160;
		height = 90;
		workswitch(1);
	}
	};

}
