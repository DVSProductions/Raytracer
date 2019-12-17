#pragma once
#include "Renderer.h"
#include "randfast.h"
#include <cinttypes>
#include <memory>
namespace cgtools {
	class cgSampling : public Renderer {
		/// <summary>
			/// Supersampling height and size
			/// </summary>
		unsigned int samples;
		/// <summary>
		/// Pointer to the renderer that provides us with an image to supersample
		/// </summary>
		std::shared_ptr<Renderer> child;
		/// <summary>
		/// Samples squared. Saves time.
		/// </summary>
		double samsq;
		/// <summary>
		/// Turbo generator
		/// </summary>
		randfast dist;
	public:
		/// <summary>
		/// Creates a new Stratified Sampler and initializes all random sources for it
		/// </summary>
		/// <param name="samples">squareroot of sample count</param>
		/// <param name="ActualRenderer"></param>
		cgSampling(short samples, std::shared_ptr<Renderer> ActualRenderer) noexcept;
		/// <summary>
		/// Super samples the contained renderer
		/// </summary>
		/// <param name="x">position to start sampling X</param>
		/// <param name="y">position to start sampling Y</param>
		/// <returns></returns>
		Color getColor(double x, double y) override;
		std::shared_ptr<Renderer> clone() override;
	};

}