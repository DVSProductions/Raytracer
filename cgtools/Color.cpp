#include "Color.h"
#include <cmath>
#include "randfast.h"
namespace cgtools {
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

	Color cgtools::Color::operator=(const Color& a) noexcept {
		r = a.r;
		g = a.g;
		b = a.b;
		return *this;
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

	Color cgtools::Color::operator/(const Color& c) const noexcept {
		return Color(c.r / r, c.g / g, c.b / b);
	}

	Color cgtools::Color::operator+(const double& a) const noexcept {
		return Color(a + r, a + g, a + b);
	}

	Color cgtools::Color::operator-(const double& a) const noexcept {
		return Color(r - a, g - a, b - a);
	}

	Color Color::operator*(const double& s) const  noexcept {
		return Color(s * r, s * g, s * b);
	}

	Color cgtools::Color::operator/(const double& a) const noexcept {
		return Color(r / a, g / a, b / a);
	}

	Color cgtools::Color::operator+=(const Color& a) noexcept {
		r += a.r;
		g += a.g;
		b += a.b;
		return this;
	}

	Color cgtools::Color::operator-=(const Color& a) noexcept {
		r -= a.r;
		g -= a.g;
		b -= a.b;
		return this;
	}

	Color cgtools::Color::operator*=(const Color& a) noexcept {
		r *= a.r;
		g *= a.g;
		b *= a.b;
		return this;
	}

	Color cgtools::Color::operator/=(const Color& a) noexcept {
		r /= a.r;
		g /= a.g;
		b /= a.b;
		return this;
	}

	Color cgtools::Color::operator+=(const double& a) noexcept {
		r += a;
		g += a;
		b += a;
		return this;
	}

	Color cgtools::Color::operator-=(const double& a) noexcept {
		r -= a;
		g -= a;
		b -= a;
		return this;
	}

	Color cgtools::Color::operator*=(const double& a) noexcept {
		r *= a;
		g *= a;
		b *= a;
		return this;
	}

	Color cgtools::Color::operator/=(const double& a) noexcept {
		r /= a;
		g /= a;
		b /= a;
		return this;
	}

	Color Color::operator/(const double& s) noexcept {
		return Color(r / s, g / s, b / s);
	}

	Color Color::clamp()const noexcept {
		return Color(fmin(1, fmax(this->r, 0)), fmin(1, fmax(this->g, 0)), fmin(1, fmax(this->b, 0)));
	}

	Color cgtools::Color::reverseGamma(const double& gamma) const noexcept {
		return Color(pow(r, gamma), pow(g, gamma), pow(b, gamma));
	}

	Color Color::hsvToRgb(const Color& hsv) noexcept {
		return (((hue(hsv.r) - c_white) * hsv.g) + c_white) * hsv.b;
	}

	std::string Color::toString()const {
		return "(Col:" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
	}

	Color Color::hue(double h) noexcept {
		return Color(abs(h * 6 - 3) - 1, 2 - abs(h * 6 - 2), 2 - abs(h * 6 - 4)).clamp();
	}

	Color Color::getRandom(std::mt19937_64 mt) {
		randfast rng(mt());
		return Color(rng(), rng(), rng());
	}

	Color cgtools::Color::fromRGB(const uint8_t& r, const uint8_t& g, const uint8_t& b) noexcept {
		return Color(r / 255.0, g / 255.0, b / 255.0);
	}

	bool Color::operator==(const Color& v) const noexcept {
		return v.r == r && v.g == g && v.b == b;
	}

	std::string cgtools::Color::serialize() const {
		return  std::to_string(r) + "|" + std::to_string(g) + "|" + std::to_string(b);
	}

	void cgtools::Color::load(std::string serialized) {
		auto ret = Serializable::split(serialized);
		f_chars(ret[0], r);
		r = pow(r, 2.2);
		f_chars(ret[1], g);
		g = pow(g, 2.2);
		f_chars(ret[2], b);
		b = pow(b, 2.2);
	}

	size_t cgtools::Color::size() const {
		return sizeof(Color);
	}

	Color operator*(const double& s, const Color& a) noexcept {
		return Color(s * a.r, s * a.g, s * a.b);
	}

	//Color operator*(const double& s, const Color& a)  noexcept {
	//	return Color(a.r * s, a.g * s, a.b * s);
	//}
}