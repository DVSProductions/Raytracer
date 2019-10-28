#pragma once
#include "Renderer.h"
using namespace cgtools;
class ColoredSquare : public Renderer {
	double left, right, top, bottom;
	Color color;
public:
	/// <summary>
	/// This simple renderer generates a square with a given size in the middle of the screen
	/// </summary>
	/// <param name="color">Color of the square</param>
	/// <param name="a">height/width of the square</param>
	/// <param name="screenX">width of our image</param>
	/// <param name="screenY">height of our image</param>
	ColoredSquare(const Color* color, int a, int screenX, int screenY) noexcept;
	/// <summary>
	/// Returns our color if the square is in that coordinate or black if is it not
	/// </summary>
	Color getColor(double x, double y)noexcept override;
};

