#include "Checkered.h"
#include "DLLInfo.h"
Checkered::Checkered(const Color* bgA, const  Color* bgB, const  Color* rect, int bgMOD, int rectA, int screenX, int screenY) :child(rect, rectA, screenX, screenY) {
	A = Color(bgA);
	B = Color(bgB);
	mod = bgMOD * 2 * scaling;
}

Color Checkered::getColor(double x, double y) {
	int ix = (int)x, iy = (int)y;
	auto c = child.getColor(ix, iy);
	return (!(c == black)) ? c : ((ix % mod >= mod / 2) ? (iy % mod < mod / 2) ? &A : &B : (iy % mod < mod / 2) ? &B : &A);
	//return !(c == black) ? c : ((x % mod >= mod / 2) && (y % mod < mod / 2) ? A : B;//kept it for sexapeal
}
