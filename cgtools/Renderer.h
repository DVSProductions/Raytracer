#pragma once
#include "Color.h"
#include <memory>
namespace cgtools {
	/// <summary>
	/// Abstract class to provide a common interface between all "default" Rendering classes
	/// </summary>
	class Renderer {
	public:
		/// <summary>
		/// Returns the color located at (x,y)
		/// </summary>
		/// <param name="x">X coordinate</param>
		/// <param name="y">Y coordinate</param>
		/// <returns>Color at position</returns>
		virtual Color getColor(double x, double y) = 0;
		virtual std::shared_ptr<Renderer> clone() = 0;
	};
}