#include "Color.h"
#include <cmath>
using namespace cgtools;
Color::Color()noexcept {
	r = 0;
	g = 0;
	b = 0;
}

Color::Color(double red, double green, double blue)noexcept {
	r = red;
	g = green;
	b = blue;
}

//Color::Color(double r, double g, double b, bool deletable) :Color(r, g, b)
//{
//	this->deletable = deletable;
//}

Color::Color(const Color* toCopy)noexcept {
	r = toCopy->r;
	g = toCopy->g;
	b = toCopy->b;
};
Color::Color(Color* toCopy)noexcept {
	r = toCopy->r;
	g = toCopy->g;
	b = toCopy->b;
}


Color Color::operator+(const Color& a) const  noexcept {
	return Color(a.r + r, a.g + g, a.b + b);
}

Color Color::operator-(const Color& a) const  noexcept {
	return Color(r - a.r, g - a.g, b - a.g);
}

Color Color::operator*(const Color& c) const  noexcept {
	return Color(c.r * r, c.g * g, c.b * b);
}

Color Color::operator*(const double& s) const  noexcept {
	return Color(s * r, s * g, s * b);
}

Color Color::operator/(const double& s) noexcept {
	return Color(r / s, g / s, b / s);
}

Color Color::clamp(const Color& v)  noexcept {
	return color(fmin(1, fmax(v.r, 0)), fmin(1, fmax(v.g, 0)), fmin(1, fmax(v.b, 0)));
}

Color Color::hsvToRgb(const Color& hsv) noexcept {
	return hsv.b * (hsv.g * (hue(hsv.r) - c_white) + c_white);
}

std::string Color::toString() {
	return "(Col:" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
}

Color Color::hue(double h) noexcept {
	return clamp(Color(abs(h * 6 - 3) - 1, 2 - abs(h * 6 - 2), 2 - abs(h * 6 - 4)));
}

Color Color::RNG(std::mt19937 mt) {
	const std::uniform_real_distribution<double> rng(0, 1);
	return Color(rng(mt), rng(mt), rng(mt));
}

bool Color::operator==(const Color& v) const noexcept {
	return v.r == r && v.g == g && v.b == b;
}

Color operator*(const double& s, const Color& a) noexcept {
	return Color(s * a.r, s * a.g, s * a.b);
}

Color cgtools::operator*(const double& s, const Color& a)  noexcept {
	return Color(a.r * s, a.g * s, a.b * s);
}
