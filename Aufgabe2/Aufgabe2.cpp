// Aufgabe2.cpp : https://tramberend.beuth-hochschule.de/lehre/19-ws/bmi-cgg/assignments/a02-page.html
//
//#include "A2Defines.h"
#include "DllInfo.h"
#include "cgtools.h"
#include "Image.h"
#include "lodepng.h"
#include <direct.h>
#include <Windows.h>
#include<vector>
#include <functional>
#include "Circle.h"
#include "CircleRenderer.h"
#include "StratifiedSampling.h"
const std::string files[] = { "a02-discs.png","a02-supersampling.png","_" };

Image* image;
Renderer* renderer;// = ConstantColor(red);
void RenderLoop() {
#if DLL_DEBUG
	cout << "->RL";
	//Sleep(100);
#endif
	for (int x = 0; x != width; x++, progress = x)
		for (int y = 0; y != height; y++) {
#if DLL_DEBUG
			cout << "->GC";
			//Sleep(10);
#endif
			auto c = renderer->getColor(x, y);
#if DLL_DEBUG
			cout << "->" << c.toString();
			//Sleep(10);
#endif
			image->setPixel(x, y, c);
#if DLL_DEBUG
			cout << "->W" << endl;
			//Sleep(10);
#endif
		}
#if DLL_DEBUG
	cout << "->Done";
	Sleep(100);
#endif
	progress = width;
}
void rendercycle(std::string filename) {
#if DLL_DEBUG
	cout << "->RC";
	Sleep(100);
#endif
	Image i(width, height, 2.2);
	image = &i;
	RenderLoop();
	lodepngReturn = image->write(filename);
}

void RenderLoopT(int offset, int total) {
#if DLL_DEBUG
	cout << "->RL";
	Sleep(1000);
#endif
	for (int x = offset; x < width; x += total, progress++)
		for (int y = 0; y != height; y++)
#if DLL_DEBUG
		{
			cout << "->GC";
			//Sleep(10);
			auto c = renderer->getColor(x, y);
			cout << "->" << c.toString();
			//Sleep(10);
			image->setPixel(x, y, c);
			//cout << "->W" << endl;
			//Sleep(10);
		}
#else
			image->setPixel(x, y, renderer->getColor(x, y));
#endif

}

void rendercycleT(std::string filename) {
#if DLL_DEBUG
	cout << "->RC";
	Sleep(1000);
#endif
	Image* i = new Image(width, height, 2.2);
	image = i;
	std::vector<std::thread*> workers;
#if DLL_DEBUG
	cout << "->LT";
	Sleep(100);
#endif
	int th = std::thread::hardware_concurrency();
	for (int n = 0; n < th; n++) {
		workers.push_back( new std::thread(RenderLoopT, n, th));
	}
	//workers[1].
#if DLL_DEBUG
	std::cout << "->Wait";
	Sleep(1000);
#endif
	for (int n = 0; n < workers.size(); n++) {
		while (!workers[n]->joinable())Sleep(100);
		workers[n]->join();
	}
#if DLL_DEBUG
	cout << "->SP";
	Sleep(2000);
#endif
	progress = width;
#if DLL_DEBUG
	cout << "->Writing";
	Sleep(2000);
#endif
	lodepngReturn = image->write(filename);
}



void RenderWorker(std::string filename, Renderer* rend) {
#if DLL_DEBUG
	cout << "->RW";
	Sleep(100);
#endif
	progress = 0;
	lodepngReturn = -1;
	renderer = rend;
#if DLL_DEBUG
	cout << "->go" << endl;
	Sleep(100);
#endif
	worker = std::thread(rendercycleT, filename);
	worker.detach();
}
//void RenderWorker(std::string filename, Renderer* rend, std::function<void()>preparation) {
//#if DLL_DEBUG
//	cout << "->RW2";
//	Sleep(100);
//#endif
//	progress = 0;
//	lodepngReturn = -1;
//	renderer = rend;
//#if DLL_DEBUG
//	cout << "->go" << endl;
//	Sleep(100);
//#endif
//	worker = std::thread(rendercyclev2, filename, preparation);
//	worker.detach();
//}

bool workswitch(int Option) {
#if DLL_DEBUG
	cout << "WS" << endl;
#endif
	switch (Option) {
	case(0):
	{
		RenderWorker(files[Option], new CircleRenderer(width, height));
		return true;
	}
	case(1):
	{
		RenderWorker(files[Option], new StratifiedSampling(10, new CircleRenderer(width, height)));
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