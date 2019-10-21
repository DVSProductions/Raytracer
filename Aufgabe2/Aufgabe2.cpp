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
/// <summary>
/// targetimage
/// </summary>
Image* image;
/// <summary>
/// Renderer storage
/// </summary>
Renderer* renderer;// = ConstantColor(red);
/// <summary>
/// Generates the colors for every pixel and updates it's progress
/// <para>
/// Upgrade with version2: MULITHREADING</para>
/// Yes this version of RenderLoop is designed to calculate every n-th line where n is the number of threads
/// </summary>
/// <param name="offset">my thread index</param>
/// <param name="total">total number of threads</param>
void RenderLoop(int offset, int total) {
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
/// <summary>
/// Allocates memory and prepares, initializes and launches render threads
/// </summary>
/// <param name="filename">output filename</param>
void rendercycle(std::string filename) {
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
		workers.push_back(new std::thread(RenderLoop, n, th));
	}
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
	workers.clear();
	progress = width;
#if DLL_DEBUG
	cout << "->Writing";
	Sleep(2000);
#endif
	lodepngReturn = image->write(filename);
}


/// <summary>
/// Launches the multithread worker
/// </summary>
/// <param name="rend">Renderer to use</param>
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
	worker = std::thread(rendercycle, filename);
	worker.detach();
}
/// <summary>
/// Decides which File to render and with what options
/// </summary>
/// <param name="Option">index of file</param>
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