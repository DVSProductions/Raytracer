#define _USE_MATH_DEFINES 
#include "CppUnitTest.h"
#include "Ray.h"
#include "A3Sphere.h"
#include "A3Sphere.cpp"
#include "DLLInfo.h"
#include "A3PinholeCamera.h"
#include "A3PinholeCamera.cpp"
#include "Camera.h"
#include "Camera.cpp"
#include "point.h"
#include "Hit.h"
#include <cmath>
#include "Aufgabe3.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace cgtools;
namespace A3Validator {
	TEST_CLASS(A3Validator) {
		std::wstring StringToWString(const std::string& s) {
			return std::wstring(s.begin(), s.end());
		}
		inline std::string str(std::string s) {
			return s;
		}
		DDD::Hit testHit(point c, point x0, direction d, double tmax) {
			A3Sphere s(c, 1, c_red);
			DDD::Ray r(x0, d, tmax, 0);
			return s.intersect(r);
		}
public:
	TEST_METHOD(A3_2_1) {
		width = 10;
		height = 10;
		auto c = A3PinholeCamera(M_PI / 2.0, cgtools::point(0, 0, 0),cgtools::c_black);
		auto r = c.generateRay(0, 0);
		Assert::IsTrue(r.x0 == point(0, 0, 0));
	}
	TEST_METHOD(A3_2_2) {
		auto c = A3PinholeCamera(M_PI / 2.0, cgtools::point(0, 0, 0), cgtools::c_black);
		auto r = c.generateRay(0, 0);
		Assert::IsTrue(r.dir.reduceAccuracy(4) == direction(-1.0 / sqrt(3), 1.0 / sqrt(3), -1.0 / sqrt(3)).reduceAccuracy(4), StringToWString("Richtung falsch: " + str(r.dir)).c_str());
	}
	TEST_METHOD(A3_2_3) {
		auto c = A3PinholeCamera(M_PI / 2.0, cgtools::point(0, 0, 0), cgtools::c_black);
		auto r = c.generateRay(5, 5);
		Assert::IsTrue(r.dir == direction(0, 0, -1), StringToWString("Richtung falsch: " + str(r.dir)).c_str());
	}
	TEST_METHOD(A3_2_4) {
		auto c = A3PinholeCamera(M_PI / 2.0, cgtools::point(0, 0, 0), cgtools::c_black);
		auto r = c.generateRay(10, 10);
		Assert::IsTrue(r.dir.reduceAccuracy(4) == point(1 / sqrt(3), -1 / sqrt(3), -1 / sqrt(3)).reduceAccuracy(4), StringToWString("Richtung falsch: " + str(r.dir)).c_str());
	}
	TEST_METHOD(TestCase1) {
		auto result = testHit(point(0, 0, -2), point(0, 0, 0), direction(0, 0, -1), INFINITY);
		Assert::IsTrue(result.hit);
		Assert::IsTrue(result.pos == point(0, 0, -1), StringToWString("Falscher Punkt " + str(result.pos)).c_str());
		Assert::IsTrue(result.n == direction(0, 0, 1), StringToWString("Normalenvektor falsch: " + str(result.n)).c_str());
	}
	TEST_METHOD(TestCase2) {
		auto result = testHit(point(0, 0, -2), point(0, 0, 0), direction(0, 1, -1), INFINITY);
		Assert::IsTrue(!result.hit);
	}
	TEST_METHOD(TestCase3) {
		auto result = testHit(point(0, -1, -2), point(0, 0, 0), direction(0, 0, -1), INFINITY);
		Assert::IsTrue(result.hit, L"Ergebnis sollte nicht null sein");
		Assert::IsTrue(result.pos == point(0, 0, -2), StringToWString("Falscher Punkt " + str(result.pos)).c_str());
		Assert::IsTrue(result.n == direction(0, 1, 0), StringToWString("Normalenvektor falsch: " + str(result.n)).c_str());
	}
	TEST_METHOD(TestCase4) {
		auto result = testHit(point(0, 0, -2), point(0, 0, -4), direction(0, 0, -1), INFINITY);
		Assert::IsTrue(result.hit, L"Ergebnis sollte null sein");
	}
	TEST_METHOD(TestCase5) {
		auto result = testHit(point(0, 0, -4), point(0, 0, 0), direction(0, 0, -1), 2);
		Assert::IsTrue(result.hit, L"Ergebnis sollte null sein");
	}
	TEST_METHOD(TestVec) {
		std::vector <DDD::renderable*> objects;
		objects.push_back(new A3Sphere(point(100, 100, 100), 50, Color(1, 0, 0)));
	}
	TEST_METHOD(TestPush) {
		Playground = std::make_shared<DDD::Scene>();
		Playground->addObject(new A3Sphere(point(100, 100, 100), 50, Color(1, 0, 0)));
	}
	/*TEST_METHOD(TestMain) {
		width = 100;
		height = 100;
		workswitch(0);
	}
	TEST_METHOD(TestMainTwice) {
		width = 100;
		height = 100;
		workswitch(0);
		Sleep(5000);
		workswitch(0);
	}*/
	TEST_METHOD(Rendering) {
		width = 200;
		height = 200;
		prepare();
		image = std::make_unique<Image>(Image(width, height, 2.2));
		RenderLoop(0, 1);
		lodepngReturn = image->write("..\\test.png");
		//system("..\\test.png");
		image.reset();
		renderer.reset();
	}
	};
}
