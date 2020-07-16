#include "CppUnitTest.h"
#include "../Aufgabe7/Aufgabe7.cpp"
#include "../cgtools/transformStack.h"
#include "../cgtools/Rotation.h"
#include "../cgtools/ComplexRotation.h"
#include "../cgtools/Translation.h"
#include "../cgtools/Matrix.h"
#include "MovablePinholeCamera.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace A7Tester {
	TEST_CLASS(A7Tester) {
public:
	std::string scene = "0!0.8&5#1.5}0.886274509803922|0.886274509803922|0.886274509803922|}0.0156862745098039|0.0156862745098039|0.0156862745098039|}#&0|-0.2|-3|&!$0!1&2#0.623529411764706|0.937254901960784|0.505882352941176|}0|0|0|}#&2|0|-5|&!$0!1&2#1|0|0|}0.0117647058823529|0.0117647058823529|0.0117647058823529|}#&0|0|-10|&!$0!1&2#0|0|1|}0.00392156862745098|0.00392156862745098|0.00392156862745098|}#&0|0|10|&!$0!1&2#0.917647058823529|0.450980392156863|0.890196078431372|}0|0|0|}#&1|0|-7|&!$0!1&2#0|1|1|}0.0156862745098039|0.0156862745098039|0.0156862745098039|}#&3|0|-3|&!$";
	std::string camera = "1!1|1|1|[1.5707963267949&0|0|0|&5&[0#2|0|0|#{1#0|10|#{[!";
	TEST_METHOD(Test_ManualCreation) {
		prepare3d();
		width = 400;
		height = 200;
		cgtools::transformStack ts;
		ts.add(std::move(std::make_unique<cgtools::Translation>(point(0, 0, 10))));
		ts.add(std::move(std::make_unique<cgtools::Rotation>(Axis::x, 10)));
		ts.add(std::move(std::make_unique<cgtools::ComplexRotation>(cgtools::direction(0, 1, 0), -10)));
		auto c = new DDD::MovablePinholeCamera(1.5, DDD::Background(cgtools::c_white), 3, ts);
		cam = (std::shared_ptr<DDD::ACamera>)c;
		playground->load(scene);
		cam->setScene(playground);
		cam->init();
		Raytracer::setsampleQuality(0);
		Raytracer::setSingleThread();
		Raytracer::RenderWorker(sceneOutputFile);
	}
	TEST_METHOD(Test_SerializedCreation) {
		prepare3d();
		width = 400;
		height = 200;
		auto c = new DDD::MovablePinholeCamera(0, DDD::Background(cgtools::Color(0, 0, 0)));
		c->load(camera);
		cam = (std::shared_ptr<DDD::ACamera>)c;
		playground->load(scene);
		cam->setScene(playground);
		cam->init();
		Raytracer::setsampleQuality(0);
		Raytracer::setFullThreadCount();
		Raytracer::RenderWorker(sceneOutputFile);
	}
#define ___amWorker(idx) std::to_string(idx)+"\n"
	TEST_METHOD(MatrixTest) {
		matrix m(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
		m *= matrix(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
		const auto s = m.toString();
		Assert::AreEqual(std::string("( 10.000000 26.000000 42.000000 58.000000 )\n( 10.000000 26.000000 42.000000 58.000000 )\n( 10.000000 26.000000 42.000000 58.000000 )\n( 10.000000 26.000000 42.000000 58.000000 )\n"), s);
	}
	TEST_METHOD(MatrixTest2) {
		const std::string s = __applyToMatrix(___amWorker, +);
		Assert::AreEqual(std::string("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n"), s);
	}
	std::string Scene2 = "4!1]3]2#0.95|0.95|0.95|}0|0|0|}#]0|0|-3|]!$";
	TEST_METHOD(CylinderTest) {
		prepare3d();
		width = 400;
		height = 200;
		cgtools::transformStack ts;
		ts.add(std::move(std::make_unique<cgtools::Translation>(point(0, 0, 10))));
		ts.add(std::move(std::make_unique<cgtools::Rotation>(Axis::x, 10)));
		ts.add(std::move(std::make_unique<cgtools::ComplexRotation>(cgtools::direction(0, 1, 0), -10)));
		auto c = new DDD::MovablePinholeCamera(1.5, DDD::Background(cgtools::c_white), 3, ts);
		cam = (std::shared_ptr<DDD::ACamera>)c;
		playground->load(Scene2);
		cam->setScene(playground);
		cam->init();
		Raytracer::setsampleQuality(0);
		Raytracer::setSingleThread();
		Raytracer::RenderWorker(sceneOutputFile);
	}
	};
}
