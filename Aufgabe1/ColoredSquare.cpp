#include "ColoredSquare.h"
#include "DLLInfo.h"
ColoredSquare::ColoredSquare(const Color* color, int a, int screenX, int screenY) noexcept {
#if DLL_DEBUG
	cout << "->CSQ()";
	Sleep(100);
#endif
	a *= scaling;
	screenX /= 2;
	screenY /= 2;
	a /= 2;
	left =static_cast<double>(screenX) - a;
	right = static_cast<double>(screenX) + a;
	top = static_cast<double>(screenY) - a;
	bottom = static_cast<double>(screenY) + a;
	this->color = Color(color);
	//blk = Color(black);
#if DLL_DEBUG
	cout << "->Created";
	Sleep(100);
#endif
}

Color ColoredSquare::getColor(double x, double y)noexcept {
	return (x > left&& x<right && y>top&& y < bottom ? &color : c_black);
}

std::shared_ptr<Renderer> ColoredSquare::clone() {
	return nullptr;
}
