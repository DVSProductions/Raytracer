#pragma once
#include <string>
#include <memory>
#include "Color.h"
namespace cgtools {
	class Image {
		/// <summary>
		/// Stores precomputed 1/gamma value
		/// </summary>
		double gamma;
		/// <summary>
		/// Storage for RGB values (allocated with NEW not malloc)
		/// Why double? Improved memory with byte!
		/// </summary>
		std::unique_ptr<uint8_t[]> buffer;
		/// <summary>
		/// Sizes of the buffer
		/// </summary>
		size_t sizeX, sizeY;
	public:
		/// <summary>
		/// Creates a new Image Buffer. Automatically allocates the required memory on Creation.
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="gamma">Gamma correction will be performed automatically</param>
		Image(size_t width, size_t height, double gamma = 1.0);
		/// <summary>
		/// Sets the color of a given pixel. Performs gamma correction
		/// </summary>
		/// <param name="x">x index</param>
		/// <param name="y">y index</param>
		/// <param name="color">color at this position</param>
		void setPixel(size_t x, size_t y, Color color) noexcept;
		/// <summary>
		/// Writes the Image to the given Path
		/// </summary>
		/// <param name="filename"></param>
		/// <returns>lodepng response code</returns>
		unsigned int write(std::string filename);
		void dump(std::string dumpName);
		size_t loadFromDump(std::string dumpNampe);
	};

}