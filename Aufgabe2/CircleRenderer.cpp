#include "CircleRenderer.h"
#include <thread>
#include <iostream>
#include <algorithm>
#include <random>
#include "DLLInfo.h"
//10% speed improvement with sort
bool cmp(const Circle& a, const Circle& b)noexcept {
	return a.radius < b.radius;//reverse list
}
CircleRenderer::CircleRenderer(int mywidth, int myheight){
	std::random_device rd;
	std::mt19937 mt(10);
	//std::mt19937 mt(rd());
	const std::uniform_int_distribution<int> rw(0, mywidth);
	const std::uniform_int_distribution<int> rh(0, myheight);
	const std::uniform_int_distribution<int> rr(myheight / 100, myheight /10);
	const int num = 50;//; std::uniform_int_distribution<int>(5000,10000)(mt);
	for (int n = 0; n < num; n++) 
		circles.push_back(Circle(rw(mt), rh(mt), rr(mt), Color::RNG(mt)));
	std::sort(circles.begin(), circles.end(), cmp);
}

Color CircleRenderer::getColor(double x, double y) {
	Circle* result = nullptr;
	const size_t l = circles.size();
	for (size_t n = 0; n != l; n++) 
		if ((result == nullptr || circles[n].radius < result->radius) && circles[n].isPointInCircle(x, y))
			result = &circles[n];
	return result == nullptr ? c_black : result->color;
}

//Color CircleRenderer::getColor(double x, double y) {
//	Circle* result = nullptr;
//	const auto end = circles.end();
//	for (auto it = circles.begin(); it != end; ++it)
//		if ((result == nullptr || it->radius < result->radius) && it->isPointInCircle(x, y))
//			result = &(*it);
//	return result == nullptr ? c_black : result->color;
//}
