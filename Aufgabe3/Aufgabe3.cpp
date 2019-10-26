#include "DllInfo.h"
#include "cgtools.h"
#include "Image.h"
#include "lodepng.h"
#include <direct.h>
#include <Windows.h>
#include<vector>
#include <functional>
#include "PinholeCamera.h"
#include "cgSampling.h"
#include "Scene.h"
#include "Sphere.h"
const std::string files[] = { "a03-one-sphere.png","_" };
DDD::Scene* Playground;
Camera* cam;
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
void RenderLoop(int offset, int total)noexcept {
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
		const auto t = workers[n];
		while (!t->joinable())Sleep(100);
		t->join();
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
void setsampleQuality(int samples = 10) {
	if(renderer!=nullptr)
	delete[]renderer;
	renderer = new cgSampling(samples, cam);
}
bool prepared = false;
void prepare() {
	if (prepared)return;
	prepared = true;
	Playground = new DDD::Scene();
	cam = new PinholeCamera(1, cgtools::point(0, 0, 0));
	cam->setScene(Playground);
	Playground->addObject(new Sphere(point(10, 10, 10), 5, c_red));
	renderer = new cgtools::cgSampling(10, cam);
}
/// <summary>
/// Decides which File to render and with what options
/// </summary>
/// <param name="Option">index of file</param>
bool workswitch(int Option) {
#if DLL_DEBUG
	cout << "WS" << endl;
#endif
	if (Option != 0)
		return false;
	prepare();
	RenderWorker(files[Option]);
	return true;
}