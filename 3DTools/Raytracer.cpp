#include "Raytracer.h"
#include "../cgtools/Image.h"
#include "../cgtools/lodepng.h"
#include "../DLLFiles/DLLInfo.h"
#include "../cgtools/cgSampling.h"
#define SingleThread false
int threadCount = 0;
using namespace cgtools;
/// <summary>
/// targetimage
/// </summary>
std::unique_ptr<Image> image;
/// <summary>
/// Renderer storage
/// </summary>
std::shared_ptr<Renderer> renderer;
std::shared_ptr <DDD::Scene> playground;//=std::shared_ptr<DDD::Scene>();
std::shared_ptr <DDD::ACamera> cam; //= std::shared_ptr<DDD::ACamera>();
/// <summary>
/// Generates the colors for every pixel and updates it's progress
/// <para>
/// Upgrade with version2: MULITHREADING</para>
/// Yes this version of RenderLoop is designed to calculate every n-th line where n is the number of threads
/// </summary>
/// <param name="offset">my thread index</param>
/// <param name="total">total number of threads</param>
void Raytracer::RenderLoop(int offset, int total) {
	for (int x = offset; x < width; x += total, progress++)
		for (int y = 0; y != height; y++)
			image->setPixel(x, y, renderer->getColor(x, y));
}

/// /// <summary>
/// Allocates memory and prepares, initializes and launches render threads
/// </summary>
/// <param name="filename">output filename</param>
void Raytracer::rendercycle(std::string filename) {
	image = std::make_unique<cgtools::Image>(cgtools::Image(width, height, 2.2));
	std::vector<std::unique_ptr<std::thread>> workers;
	for (int n = 0; n < threadCount; n++) 
		workers.push_back(std::make_unique<std::thread>(std::thread(RenderLoop, n, threadCount)));
	for (int n = 0; n < workers.size(); n++) {
		while (!workers.at(n)->joinable())
			Sleep(50);
		workers.at(n)->join();
	}
	workers.clear();
	progress = width;
	lodepngReturn = image->write(filename);
	image.reset();
}

/// <summary>
/// Launches the multithread worker
/// </summary>
/// <param name="rend">Renderer to use</param>
void Raytracer::RenderWorker(std::string filename) {
	progress = 0;
	lodepngReturn = -1;
	worker = std::thread(Raytracer::rendercycle, filename);
	worker.detach();
}

void Raytracer::setsampleQuality(int samples) {
	if (renderer != nullptr)
		renderer.reset();
	if (samples == 0)renderer = cam;
	else
		renderer = std::make_shared<cgSampling>(cgSampling(samples, cam));
}
#if SingleThread
void Raytracer::setPreviewThreadCount() {
	threadCount = 1;
}

void Raytracer::setFullThreadCount() {
	threadCount = 1;
}
#else
void Raytracer::setPreviewThreadCount() {
	threadCount = 1 + std::thread::hardware_concurrency() / 2;
}

void Raytracer::setFullThreadCount() {
	threadCount = std::thread::hardware_concurrency();
}
#endif