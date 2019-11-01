#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <direct.h>
#include <Windows.h>
#include <vector>
#include <functional>
#include <memory>

#include "3DInfo.h"
#include "Scene.h"
#include "ACamera.h"
#include "DllInfo.h"
#include "cgtools.h"
#include "Image.h"
#include "lodepng.h"
#include "cgSampling.h"
#include "PinholeCamera.h"
#include "Sphere.h"
/// <summary>
/// -1 terminated array of Supported Element classes
/// </summary>
const int supportedClasses[] = { 0,-1 };
const std::string files[] = { "a03-one-sphere.png","_" };
const std::string libVersion = "2.0";
std::shared_ptr <DDD::Scene> playground;//=std::shared_ptr<DDD::Scene>();
std::shared_ptr <DDD::ACamera> cam; //= std::shared_ptr<DDD::ACamera>();
void prepare3d() {
	return;
}
/// <summary>
/// targetimage
/// </summary>
std::unique_ptr<Image> image;
/// <summary>
/// Renderer storage
/// </summary>
std::unique_ptr<Renderer> renderer;
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
	image = std::make_unique<Image>(Image(width, height, 2.2));
	std::vector<std::unique_ptr<std::thread>> workers;
#if DLL_DEBUG
	cout << "->LT";
	Sleep(100);
#endif
	int th = std::thread::hardware_concurrency();
	for (int n = 0; n < th; n++) {
		workers.push_back(std::make_unique<std::thread>(std::thread(RenderLoop, n, th)));
	}
#if DLL_DEBUG
	std::cout << "->Wait";
	Sleep(1000);
#endif
	for (int n = 0; n < workers.size(); n++) {
		while (!workers.at(n)->joinable())Sleep(100);
		workers.at(n)->join();
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
	image.reset();
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
	if (renderer != nullptr)
		renderer.reset();
	renderer = std::make_unique<cgSampling>(cgSampling(samples, cam));
}
bool prepared = false;
void prepare() {
	if (prepared)return;
	prepared = true;
	playground = std::make_shared <DDD::Scene>();
	//Playground->addObject(new Sphere(point(100, 100, 100), 50, c_red));
	const Color gray = Color::fromRGB(60, 60, 60).reverseGamma(2.2);//application background color
	const Color red = Color::fromRGB(0x9B, 0x55, 0x55).reverseGamma(2.2);//application default red color
	const Color b = Color(0, 0, 1);
	cam = std::make_shared < DDD::PinholeCamera>(DDD::PinholeCamera(M_PI / 2, cgtools::point(0, 0, 0), gray));
	cam->setScene(playground);
	playground->addObject(new DDD::Sphere(point(00, 0, -3), 1.0, red));
	playground->addObject(new DDD::Sphere(point(01, 0, -3), 0.5, b));
	playground->addObject(new DDD::Sphere(point(-1, 0, -3), 0.5, b));
	setsampleQuality();
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