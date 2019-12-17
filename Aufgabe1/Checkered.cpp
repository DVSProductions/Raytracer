#include "Checkered.h"
#include "DLLInfo.h"
Checkered::Checkered(const Color* bgA, const  Color* bgB, const  Color* rect, int bgMOD, int rectA, int screenX, int screenY) {
	child = std::make_unique<ColoredSquare>(ColoredSquare(rect, rectA, screenX, screenY));
	A = Color(bgA);
	B = Color(bgB);
	mod = bgMOD * 2 * scaling;
}

Color Checkered::getColor(double x, double y)noexcept {
	const int ix = static_cast<int>(x), iy = static_cast<int>(y);
	const auto c = child->getColor(ix, iy);
	return (!(c == c_black)) ? c : ((ix % mod >= mod / 2) ? (iy % mod < mod / 2) ? &A : &B : (iy % mod < mod / 2) ? &B : &A);
	//return !(c == black) ? c : ((x % mod >= mod / 2) && (y % mod < mod / 2) ? A : B;//kept it for sexapeal
}

std::shared_ptr<Renderer> Checkered::clone() {
	return nullptr;
}
