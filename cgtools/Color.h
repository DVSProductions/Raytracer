#pragma once
#include <string>
#include <initializer_list>
#include <random>
#define color(r,g,b) Color(r,g,b)
/// <summary>
/// Class to do all sorts of color-y stuff
/// </summary>
class Color {
public:	
	/// <summary>
	/// I trust you on this one. DO NOT SET ABOVE 1 NOR BELOW 0
	/// </summary>
	double r, g, b;
	//bool deletable=false;
	Color() noexcept;
	/// <summary>
	/// Creates a color with specified RGB values
	/// </summary>
	Color(double r,double g, double b) noexcept;
	//Color(double r,double g, double b,bool deletable);
	/// <summary>
	/// Generates a copy of another Color object (for safe keeping)
	/// </summary>
	/// <param name="toCopy">Color to clone</param>
	Color(const Color* toCopy) noexcept;
	/// <summary>
	/// Generates a copy of another Color object (for safe keeping)
	/// </summary>
	/// <param name="toCopy">Color to clone</param>
	Color(Color* toCopy) noexcept;
	Color operator+(const Color &a) noexcept;
	Color operator-(const Color &a) noexcept;
	Color operator*(const Color &c) noexcept;
	Color operator*(const double &s) noexcept;
	friend Color operator*(const double &s, const Color &a) noexcept;
	Color operator/(const double &s)noexcept;
	static Color clamp(const Color &v) noexcept;
	static Color hsvToRgb(const Color &hsv) noexcept;
	static Color hue(double h) noexcept;
	static Color RNG(std::mt19937 mt);
	std::string toString();
	bool operator==(const Color &c) noexcept;
};

static const Color c_black = Color(0, 0, 0);
static const Color c_gray = Color(0.5, 0.5, 0.5);
static const Color c_white = Color(1, 1, 1);
static const Color c_red = Color(1, 0, 0);
static const Color c_green = Color(0, 1, 0);
static const Color c_blue = Color(0, 0, 1);
