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
	Color();
	/// <summary>
	/// Creates a color with specified RGB values
	/// </summary>
	Color(double r,double g, double b);
	//Color(double r,double g, double b,bool deletable);
	/// <summary>
	/// Generates a copy of another Color object (for safe keeping)
	/// </summary>
	/// <param name="toCopy">Color to clone</param>
	Color(const Color* toCopy);
	/// <summary>
	/// Generates a copy of another Color object (for safe keeping)
	/// </summary>
	/// <param name="toCopy">Color to clone</param>
	Color(Color* toCopy);
	~Color();
	/// <summary>
	/// Adds two or more Colors together and returns the compound result
	/// </summary>
	/// <param name="vs">Write additional colors as {<see cref="Color"/>(),<see cref="Color"/>()}</param>
	/// <returns></returns>
	static Color add(Color a, Color b, std::initializer_list<Color> vs = {});
	/// <summary>
	/// Subtracts one or more colors from a and returns the result
	/// </summary>
	/// <param name="a">Start color</param>
	/// <param name="vs">Write additional colors as {<see cref="Color"/>(),<see cref="Color"/>()}</param>
	/// <returns></returns>
	static Color subtract(Color a, Color b, std::initializer_list<Color> vs = {});
	static Color multiply(double s, Color a);
	static Color multiply(Color a, double s);
	static Color multiply(Color a, Color b);
	static Color divide(Color a, double s);
	static Color clamp(Color v);
	static Color hsvToRgb(Color hsv);
	static Color hue(double h);
	static Color RNG(std::mt19937 mt);
	std::string toString();
	bool operator==(Color c);
};

static const Color black = color(0, 0, 0);
static const Color gray = color(0.5, 0.5, 0.5);
static const Color white = color(1, 1, 1);
static const Color red = color(1, 0, 0);
static const Color green = color(0, 1, 0);
static const Color blue = color(0, 0, 1);
