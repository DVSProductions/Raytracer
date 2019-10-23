// Aufgabe1.cpp : https://tramberend.beuth-hochschule.de/lehre/19-ws/bmi-cgg/assignments/a01-page.html
#include "DllInfo.h"
#include "cgtools.h"
#include "Image.h"
#include "ConstantColor.h"
#include "ColoredSquare.h"
#include "lodepng.h"
#include <direct.h>
#include "Checkered.h"
#include <Windows.h>
const std::string files[] = { "a01-image.png","a01-square.png","a01-checkered-background.png","_" };

Image* image;
Renderer* renderer;// = ConstantColor(red);
/// <summary>
/// Generates the colors for every pixel and updates it's progress
/// </summary>
void RenderLoop() noexcept {
#if DLL_DEBUG
	cout << "->RL";
	Sleep(100);
#endif
	for (int x = 0; x != width; x++, progress = x)
		for (int y = 0; y != height; y++) {
#if DLL_DEBUG
			cout << "->GC";
			Sleep(10);
#endif
			image->setPixel(x, y, renderer->getColor(x, y));
#if DLL_DEBUG
			cout << "->W" << endl;
			Sleep(10);
#endif
		}
#if DLL_DEBUG
	cout << "->Done";
	Sleep(100);
#endif
	progress = width;
}
/// <summary>
/// Allocates memory and executes render loop
/// </summary>
/// <param name="filename"></param>
void rendercycle(std::string filename) {
#if DLL_DEBUG
	cout << "->RC";
	Sleep(100);
#endif
	Image i(width, height);
	image = &i;
	RenderLoop();
	lodepngReturn = image->write(filename);
	image = nullptr;
}
/// <summary>
/// Launches the render thread
/// </summary>
/// <param name="filename">output file</param>
void RenderWorker(std::string filename) {
#if DLL_DEBUG
	cout << "->RW";
	Sleep(100);
#endif
	progress = 0;
	lodepngReturn = -1;
#if DLL_DEBUG
	cout << "->go" << endl;
	Sleep(100);
#endif
	worker = std::thread(rendercycle, filename);
	worker.detach();
}
/// <summary>
/// Decides which File to render and with what options
/// </summary>
/// <param name="Option">fileIDX</param>
bool workswitch(int Option) {
#if DLL_DEBUG
	cout << "WS" << endl;
#endif
	switch (Option) {
	case(0):
		renderer = new ConstantColor(&c_red);
		break;
	case(1):
		renderer = new ColoredSquare(&color(1, 1, 0), 15, width, height);
		break;
	case(2):
		renderer = new Checkered(&c_gray, &c_white, &color(1, 1, 0), 1, 15, width, height);
		break;
	default:
		return false;
	}
	RenderWorker(files[Option]);
	return true;
}