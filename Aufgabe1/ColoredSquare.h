#pragma once
#include "Renderer.h"
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
	ColoredSquare(const Color* color, int a, int screenX, int screenY);
	/// <summary>
	/// Returns our color if the square is in that coordinate or black if is it not
	/// </summary>
	Color getColor(int x, int y);
	/// <summary>
	/// We don't need double precision here
	/// </summary>
	inline Color getColor(double x, double y) { return getColor((int)x, (int)y); }
};

