#pragma once
#include "Color.h"
/// <summary>
/// This class describes a circle in 2d space
/// </summary>
class Circle
{
	double x;
	double y;
	double boundXP, boundXN;
	double boundYP, boundYN;
	double innerYP, innerYN;
	double innerXP, innerXN;
public:
	/// <summary>
	/// Color of this Circle. Please don't write
	/// </summary>
	Color color;
	/// <summary>
	/// Radius of this circle, please don't write
	/// </summary>
	double radius;
	/// <summary>
	/// Creates a circle with a given position, size and color
	/// <para>
	///		The constructor also generates a few optimizations that can really reduce computation costs by 
	///		calculating the inner and outer bounds of the circle. 
	///		this allows us to avoid having to compute square-roots in favor of just comparing some values
	/// </para>
	/// </summary>
	/// <param name="x">X position</param>
	/// <param name="y">Y position</param>
	/// <param name="radius">radius of the circle</param>
	/// <param name="c">Color</param>
	Circle(double x, double y, double radius, Color c)noexcept;
	/// <summary>
	/// Detects if Point is within circle
	/// </summary>
	bool isPointInCircle(double x, double y)noexcept;
};

