#pragma once
#include "Renderer.h"
#include <random>
class cgSampling :	public Renderer {
	/// <summary>
		/// Supersampling height and size
		/// </summary>
	int samples;
	/// <summary>
	/// Pointer to the renderer that provides us with an image to supersample
	/// </summary>
	Renderer* child;
	/// <summary>
	/// Samples squared. Saves time.
	/// </summary>
	double samsq;
	/// <summary>
	/// Twister generator
	/// </summary>
	std::mt19937 mt;
	/// <summary>
	/// Uniform generator for sampling positions
	/// </summary>
	std::uniform_real_distribution<double> dist;
public:
	/// <summary>
	/// Creates a new Stratified Sampler and initializes all random sources for it
	/// </summary>
	/// <param name="samples">squareroot of sample count</param>
	/// <param name="ActualRenderer"></param>
	cgSampling(uint16_t samples, Renderer* ActualRenderer);
	/// <summary>
	/// Super samples the contained renderer
	/// </summary>
	/// <param name="x">position to start sampling X</param>
	/// <param name="y">position to start sampling Y</param>
	/// <returns></returns>
	 Color getColor(double x, double y) noexcept override;
};

