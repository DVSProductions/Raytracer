#include "CppUnitTest.h"
#include "../Aufgabe6/Aufgabe6.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace A6Tester
{
	TEST_CLASS(A6Tester)
	{
	public:
		std::string camera = "0!0.827450980392157|0.827450980392157|0.827450980392157|[1.5707963267949&0|0|0|&5&[!";
		std::string scene = "0!0.8&5#1.5}0.886274509803922|0.886274509803922|0.886274509803922|}0.0156862745098039|0.0156862745098039|0.0156862745098039|}#&0|-0.2|-3|&!$0!1&2#0.623529411764706|0.937254901960784|0.505882352941176|}0|0|0|}#&2|0|-5|&!$0!1&2#1|0|0|}0.0117647058823529|0.0117647058823529|0.0117647058823529|}#&0|0|-10|&!$0!1&2#0|0|1|}0.00392156862745098|0.00392156862745098|0.00392156862745098|}#&0|0|10|&!$0!1&2#0.917647058823529|0.450980392156863|0.890196078431372|}0|0|0|}#&1|0|-7|&!$0!1&2#0|1|1|}0.0156862745098039|0.0156862745098039|0.0156862745098039|}#&3|0|-3|&!$";
		void loadScene() {
			prepare3d();
			playground->load(scene);
			auto sh = DDD::ACamera::createFromSerialization(camera);
			if (cam != nullptr) {
				cam.reset();
				cam.swap(sh);
			}
			else
				cam = sh;
			cam->setScene(playground);
		}
		TEST_METHOD(TestMethod1){
			loadScene();
			width =400;
			height = 200;
			cam->init();
			cam->setScene(playground);
			Raytracer::setsampleQuality(0);
			Raytracer::setSingleThread();
			Raytracer::RenderWorker(sceneOutputFile);
		}
	};
}
