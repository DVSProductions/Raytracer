#pragma once
#include "Renderer.h"
#include <vector>
#include "Circle.h"
using namespace cgtools;
class CircleRenderer :public Renderer {
	/// <summary>
	/// <see cref="Circle"/> storage
	/// </summary>
	std::vector<Circle> circles;
public:
	/// <summary>
	/// Generates a random number of circles and allows you to render it
	/// <para>The size of these circles is depended on the size of the image
	/// </para>
	/// </summary>
	/// <param name="width">height of the image</param>
	/// <param name="height">width of the image</param>
	CircleRenderer(int width, int height);
	Color getColor(double x, double y) noexcept override;
};

