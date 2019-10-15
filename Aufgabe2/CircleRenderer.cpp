#include "CircleRenderer.h"
#include <thread>
#include <iostream>
CircleRenderer::CircleRenderer(int width, int height) {
	srand(time(0));
	int num = rand() % 200 + 50;
	for (int n = 0; n < num; n++) {
		auto c = Color::RNG();
		//std::cout << c.toString() << std::endl;
		circles.push_back(Circle(rand() % width, rand() % height, (rand() % (height / 30)) + 10, c));
	}
}

Color CircleRenderer::getColor(double x, double y) {
	Circle* result = nullptr;
	for (size_t n = 0, l = circles.size(); n != l; n++) {
		if ((result == nullptr || circles[n].radius < result->radius) && circles[n].isPointInCircle(x, y))
			result = &circles[n];
	}
	/*if(result!=nullptr)
		std::cout << result->color.toString() << std::endl;*/
	return result == nullptr ? black : result->color;
}
