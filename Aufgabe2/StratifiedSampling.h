#pragma once
#include "Renderer.h"
#include <random>
/// <summary>
/// The Stratified Sampling class implements a very easy way to super sample any other renderer
/// <para>
///		it will super sample any given renderer using stratified Sampling
/// </para>
/// Randomness is guaranteed by the Mersenne Twister kindly provided by the random stdlib
/// </summary>
class StratifiedSampling : public Renderer {
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
	/// <param name="samples"></param>
	/// <param name="ActualRenderer"></param>
	StratifiedSampling(int samples, Renderer* ActualRenderer);
	/// <summary>
	/// Super samples the contained renderer
	/// </summary>
	/// <param name="x">position to start sampling X</param>
	/// <param name="y">position to start sampling Y</param>
	/// <returns></returns>
	Color getColor(double x, double y);
};

