#define _USE_MATH_DEFINES 
#include "CppUnitTest.h"
#include "Ray.h"
#include "Ray.cpp"
#include "Sphere.h"
#include "Sphere.cpp"
#include "DLLInfo.h"
#include "PinholeCamera.h"
#include "PinholeCamera.cpp"
#include "Camera.h"
#include "Camera.cpp"
#include "point.h"
#include "Hit.h"
#include "Hit.cpp"
#include <cmath>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace DDD;
using namespace cgtools;
bool workswitch(int i) {
	return false;
}
const std::string files[] = { "_" };
namespace A3Validator {
	TEST_CLASS(A3Validator) {		
		std::wstring StringToWString(const std::string& s) {
			return std::wstring(s.begin(), s.end());
		}
		inline std::string str(std::string s) {
			return s;
		}
		Hit* testHit(point c, point x0, direction d, double tmax) {
			Sphere s(c, 1, c_red);
			Ray r(x0, d, tmax, 0);
			return s.intersect(r);
		}
public:
	
	TEST_METHOD(TestCase1) {
		auto result = testHit(point(0, 0, -2), point(0, 0, 0), direction(0, 0, -1), INFINITY);
		Assert::IsNotNull(result);
		Assert::IsTrue(result->pos == point(0, 0, -1), StringToWString("Falscher punkt " + str(result->pos)).c_str());
		Assert::IsTrue(result->n == direction(0, 0, 1), StringToWString("Normalenvektor falsch: " + str(result->n)).c_str());
	}
	TEST_METHOD(TestCase2) {
		auto result = testHit(point(0, 0, -2), point(0, 0, 0), direction(0, 1, -1), INFINITY);
		Assert::IsNull(result);
	}
	TEST_METHOD(TestCase3) {
		auto result = testHit(point(0, -1, -2), point(0, 0, 0), direction(0, 0, -1), INFINITY);
		Assert::IsNotNull(result,L"Ergebnis sollte nicht null sein");
		Assert::IsTrue(result->pos == point(0, 0, -2), StringToWString("Falscher punkt "+ str(result->pos)).c_str());
		Assert::IsTrue(result->n == direction(0, 1, 0), StringToWString("Normalenvektor falsch: " + str(result->n)).c_str());
	}
	TEST_METHOD(TestCase4) {
		auto result = testHit(point(0, 0, -2), point(0, 0, -4), direction(0, 0, -1), INFINITY);
		Assert::IsNull(result,L"Ergebnis sollte null sein");
	}
	TEST_METHOD(TestCase5) {
		auto result = testHit(point(0, 0, -4), point(0, 0, 0), direction(0, 0, -1), 2);
		Assert::IsNull(result, L"Ergebnis sollte null sein");
	}
	};
}
