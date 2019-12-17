#pragma once
#include "Renderer.h"
#include "ColoredSquare.h"
#include <memory>
class Checkered : public Renderer {
	/// <summary>
	/// Background colors
	/// </summary>
	Color A, B;
	/// <summary>
	/// Modulo parameter
	/// </summary>
	int mod;
	/// <summary>
	/// Generates the square for us
	/// </summary>
	std::unique_ptr<ColoredSquare> child;
public:
	/// <summary>
	/// Creates a new Checkered Image Renderer<para>
	/// The Checkered Renderer First instantiates a ColoredSquare Renderer in order to generate the square in the middle.
	/// The rest of the pattern is calculated with modulo
	/// </para>
	/// </summary>
	/// <param name="bgA">First background color</param>
	/// <param name="bgB">Second background color</param>
	/// <param name="rect">Color of the rectangle</param>
	/// <param name="bgMOD">size of the checkers pattern</param>
	/// <param name="rectA">Rectangle height/width</param>
	/// <param name="screenX">total width</param>
	/// <param name="screenY">total height</param>
	Checkered(const Color* bgA, const Color* bgB, const Color* rect, int bgMOD, int rectA, int screenX, int screenY);
	/// <summary>
	/// This GetColor method first calls the ColoredSquare renderer to find the square in the middle, and then calculates
	/// the pattern using modulo if the ColoredSquare returns black
	/// </summary>
	Color getColor(double x, double y) noexcept override;
	std::shared_ptr<Renderer> clone()override;

};

