#include "ColoredSquare.h"
#include "DLLInfo.h"
ColoredSquare::ColoredSquare(const Color * color, int a, int screenX, int screenY) {
#if DLL_DEBUG
	cout << "->CSQ()";
	Sleep(100);
#endif
	a *= scaling;
	screenX /= 2;
	screenY /= 2;
	a /= 2;
	left = screenX - a;
	right = screenX + a;
	top = screenY - a;
	bottom = screenY + a;
	this->color = Color(color);
	//blk = Color(black);
#if DLL_DEBUG
	cout << "->Created";
	Sleep(100);
#endif
}

Color ColoredSquare::getColor(int x, int y) {
	return (x > left&& x<right && y>top&& y < bottom ? &color :black);
}
