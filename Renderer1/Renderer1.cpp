// Aufgabe1.cpp : https://tramberend.beuth-hochschule.de/lehre/19-ws/bmi-cgg/assignments/a01-page.html
//
#include "A1Defines.h"
#include "DllInfo.h"
#include "cgtools.h"
#include "Image.h"
#include "ConstantColor.h"
#include "ColoredSquare.h"
#include "lodepng.h"
#include <direct.h>
#include "Checkered.h"
#include <Windows.h>
Image* image;
ColorFunc* renderer;// = ConstantColor(red);
void RenderLoop() {
	for (int x = 0; x != width; x++, progress = x)
		for (int y = 0; y != height; y++)
			image->setPixel(x, y, renderer->getColor(x, y));
	progress = width;
}

void rendercycle(std::string filename) {
	Image i(width, height);
	image = &i;
	RenderLoop();
	lodepngReturn = image->write(filename);
}
void RenderWorker(std::string filename, ColorFunc* rend) {
	progress = 0;
	lodepngReturn = -1;
	renderer = rend;
	worker = std::thread(rendercycle, filename);
}
bool workswitch(int Option) {
	switch (Option) {
		case(0):
		{
			RenderWorker(files[Option], new ConstantColor(red));
			return true;
		}
		case(1):
		{
			RenderWorker(files[Option], new ColoredSquare(color(1, 1, 0), 15, width, height));
			true;
		}
		case(2):
		{
			RenderWorker(files[Option], new Checkered(gray, white, color(1, 1, 0), 1, 15, width, height));
			return true;
		}
		default:
			return false;
	}
}
//int main() {
//	_mkdir("..\\doc");
//	std::cout << "DVSProductions RAYTRACER" << std::endl;
//	/*rendercycle("..\\doc\\a01-image.png", ConstantColor(red));
//	rendercycle("..\\doc\\a01-square.png", ColoredSquare(color(1, 1, 0), 15 * scaling, width, height));
//	rendercycle("..\\doc\\a01-checkered-background.png", Checkered(gray, white, color(1, 1, 0), 1 * scaling, 15 * scaling, width, height));
//*/
//}