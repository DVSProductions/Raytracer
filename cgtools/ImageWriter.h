#pragma once
#include "cgtools.h"
#include <string>
#include <cmath>
namespace cgtools {
	static class ImageWriter {
		/// <summary>
		/// Ensures that the value is between 0 and 1
		/// </summary>
		/// <param name="v"></param>
		/// <returns></returns>
		static double clamp(double v) noexcept {
			return fmin(fmax(0, v), 1);
		}
	public:
		/// <summary>
		/// Creates a PNG image file (Abstracts lodepng)
		/// </summary>
		/// <param name="filename">path to file</param>
		/// <param name="data">RGB values! NO ALPHA! (yet)</param>
		/// <param name="width">width of the output image</param>
		/// <param name="height">height of the output image</param>
		/// <param name="linear">seems to be irrelevant. leave at true</param>
		/// <returns></returns>
		static unsigned int write(std::string filename, const std::unique_ptr<double[]>& data, size_t width, size_t height, bool linear = true);
	}ImageWriter;
}