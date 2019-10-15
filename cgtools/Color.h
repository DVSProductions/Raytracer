#pragma once
#include <string>
#include <initializer_list>
#define color(r,g,b) Color(r,g,b)

class Color {
public:	
	double r, g, b;
	Color();
	Color(double r,double g, double b);
	Color(const Color* toCopy);
	Color(Color* toCopy);
	~Color();
	static Color add(Color a, Color b, std::initializer_list<Color> vs = {});
	static Color subtract(Color a, Color b, std::initializer_list<Color> vs = {});
	static Color multiply(double s, Color a);
	static Color multiply(Color a, double s);
	static Color multiply(Color a, Color b);
	static Color divide(Color a, double s);
	static Color clamp(Color v);
	static Color hsvToRgb(Color hsv);
	static Color hue(double h);
	static Color RNG();
	std::string toString();
	bool operator==(Color c);
};

static const Color black = color(0, 0, 0);
static const Color gray = color(0.5, 0.5, 0.5);
static const Color white = color(1, 1, 1);
static const Color red = color(1, 0, 0);
static const Color green = color(0, 1, 0);
static const Color blue = color(0, 0, 1);
