#include "Color.h"
#include <cmath>

Color::Color() {
	r = 0;
	g = 0;
	b = 0;
}

Color::Color(double red, double green, double blue) {
	r = red;
	g = green;
	b = blue;
}

Color::~Color() {
}

Color Color::add(Color a, Color b, std::initializer_list<Color> vs) {
	Color r = color(a.r + b.r, a.g + b.g, a.b + b.b);
	for (Color v : vs)
		r = color(r.r + v.r, r.g + v.g, r.b + v.b);
	return r;
}

Color Color::subtract(Color a, Color b, std::initializer_list<Color> vs) {
	Color r = color(a.r - b.r, a.g - b.g, a.b - b.b);
	for (Color v : vs) 
		r = color(r.r - v.r, r.g - v.g, r.b - v.b);
	return r;
}

Color Color::multiply(double s, Color a) {
	return color(s * a.r, s * a.g, s * a.b);
}

Color Color::multiply(Color a, double s) {
	return multiply(s, a);
}

Color Color::multiply(Color a, Color b) {
	return color(a.r * b.r, a.g * b.g, a.b * b.b);
}

Color Color::divide(Color a, double s) {
	return color(a.r / s, a.g / s, a.b / s);
}

Color Color::clamp(Color v) {
	return color(fmin(1, fmax(v.r, 0)), fmin(1, fmax(v.g, 0)), fmin(1, fmax(v.b, 0)));
}

Color Color::hsvToRgb(Color hsv) {
	return multiply(hsv.b, add(multiply(hsv.g, subtract(hue(hsv.r), white)), white));
}

std::string Color::toString() {
	return "(Col:" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}

Color Color::hue(double h) {
	return clamp(color(abs(h * 6 - 3) - 1, 2 - abs(h * 6 - 2), 2 - abs(h * 6 - 4)));
}

bool Color::operator==(Color v) {
	return v.r == r && v.g == g && v.b == b;
}
