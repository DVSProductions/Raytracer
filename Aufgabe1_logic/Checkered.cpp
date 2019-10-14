#include "Checkered.h"
#include "A1Defines.h"
Checkered::Checkered(Color bgA, Color bgB, Color rect, int bgMOD, int rectA, int screenX, int screenY) :child(rect, rectA, screenX, screenY) {
	A = bgA;
	B = bgB;
	mod = bgMOD * 2 * scaling;
}

Color Checkered::getColor(int x, int y) {
	auto c = child.getColor(x, y);
	return !(c == black) ? c : ((x % mod >= mod / 2) ? (y % mod < mod / 2) ? A : B : (y % mod < mod / 2) ? B : A);
	//return !(c == black) ? c : ((x % mod >= mod / 2) && (y % mod < mod / 2) ? A : B;//kept it for sexapeal
}
