#include "CircleRenderer.h"
#include <thread>
#include <iostream>
#include <algorithm>
#include <random>
#include "DLLInfo.h"
//10% speed improvement with sort
bool cmp(const Circle& a, const Circle& b) {
	return a.radius < b.radius;//reverse list
}
CircleRenderer::CircleRenderer(int width, int height) {
	std::random_device rd;
	//std::mt19937 mt(10);
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> rw(0, width);
	std::uniform_int_distribution<int> rh(0, height);
	std::uniform_int_distribution<int> rr(height / 100, height /10);
	int num = std::uniform_int_distribution<int>(5000,10000)(mt);
	for (int n = 0; n < num; n++) 
		circles.push_back(Circle(rw(mt), rh(mt), rr(mt), Color::RNG(mt)));
	std::sort(circles.begin(), circles.end(), cmp);
}

Color CircleRenderer::getColor(double x, double y) {
	Circle* result = nullptr;
	for (size_t n = 0, l = circles.size(); n != l; n++) 
		if ((result == nullptr || circles[n].radius < result->radius) && circles[n].isPointInCircle(x, y))
			result = &circles[n];
	return result == nullptr ? black : result->color;
}
