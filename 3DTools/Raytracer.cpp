#include "Raytracer.h"
#include "../cgtools/Image.h"
#include "../cgtools/lodepng.h"
#include "../DLLFiles/DLLInfo.h"
#include "../cgtools/cgSampling.h"
#include <chrono>
#ifdef _WIN64 
#include <filesystem>
#include <Windows.h>
#else 
#define Sleep(duration) std::this_thread::sleep_for(std::chrono::milliseconds(duration))
#endif
#define SingleThread false
bool abortRender = false, pause = false, dumpStates = false, enableRecoveries = false;
uint_fast16_t threadCount = 0;
//bool abort = false;
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
std::shared_ptr <DDD::GameCamera> gameCam; //= std::shared_ptr<DDD::ACamera>();

void handlePause() noexcept {
	while (pause) {
#ifdef _WIN64 
		Sleep(1000);
#else
		std::this_thread::sleep_for(std::chrono::seconds(1));
#endif
	}
}
/// <summary>
/// Generates the colors for every pixel and updates it's progress
/// <para>
/// Upgrade with version2: MULITHREADING</para>
/// Yes this version of RenderLoop is designed to calculate every n-th line where n is the number of threads
/// </summary>
/// <param name="offset">my thread index</param>
/// <param name="total">total number of threads</param>
void Raytracer::RenderLoop(uint_fast32_t offset, uint_fast32_t total, std::shared_ptr<cgtools::Renderer> target) {
	for (uint_fast32_t x = offset; x < width && !abortRender; x += total, progress++)
		for (uint_fast32_t y = 0; y != height && !abortRender; y++) {
			//if (pause)handlePause();
			image->setPixel(x, y, target->getColor(x, y));
		}
}
/// /// <summary>
/// Allocates memory and prepares, initializes and launches render threads
/// </summary>
/// <param name="filename">output filename</param>
void Raytracer::rendercycle(std::string filename) {
	//using namespace std::chrono_literals;
	image = std::make_unique<cgtools::Image>(cgtools::Image(width, height, 2.2));
	if (threadCount != -1) {
		std::vector<std::unique_ptr<std::thread>> workers;
		for (uint_fast16_t n = 0; n < threadCount; n++)
			workers.push_back(std::make_unique<std::thread>(std::thread(RenderLoop, n, threadCount, renderer->clone())));
		const auto tc = threadCount;
		for (uint_fast16_t n = 0; n != tc; n++) {
			while (!workers.at(n)->joinable()) {
				//std::this_thread::sleep_for(100ms);
				Sleep(100);
			}
			workers.at(n)->join();
			threadCount--;
		}
		workers.clear();
	}
	else RenderLoop(0, 1, renderer);
	progress = width;
	if (!abortRender)
		lodepngReturn = image->write(filename);
	image.reset();
	abortRender = false;
}
Image TurboImage = Image(1, 1);
void Raytracer::TurboRenderLoop(uint_fast32_t offset, uint_fast32_t total, std::shared_ptr<cgtools::Renderer> target) {
	for (uint_fast32_t x = offset; x < width && !abortRender; x += total, progress++)
		for (uint_fast32_t y = 0; y != height && !abortRender; y++)
			TurboImage.setPixel(x, y, target->getColor(x, y));
}
void Raytracer::turboRendercycle(double gamma) {
	if (TurboImage.getX() == 1 || TurboImage.getX() != width || TurboImage.getY() != height)
		TurboImage = cgtools::Image(width, height, gamma);
	std::vector<std::thread> workers;
	for (uint_fast16_t n = 0; n < threadCount; n++)
		workers.push_back(std::thread(TurboRenderLoop, n, threadCount, renderer->clone()));
	const auto tc = threadCount;
	for (uint_fast16_t n = 0; n != tc; n++) {
		while (!workers.at(n).joinable()) {
			//std::this_thread::sleep_for(100ms);
			Sleep(1);
		}
		workers.at(n).join();
	}
	workers.clear();
	progress = width;

}

void Raytracer::prepareTurboRender(int FSAA, int threads) {
	threadCount = threads;
	gameCam->setScene(playground);
	if (renderer != nullptr)
		renderer.reset();
	if (FSAA <= 1)renderer = gameCam;
	else
		renderer = std::make_shared<cgSampling>(FSAA, gameCam);
}

void Raytracer::turboRender(int x, int y, double gamma) {
	width = x;
	height = y;
	gameCam->init();
	progress = 0;
	worker = std::thread(Raytracer::turboRendercycle, gamma);
	worker.detach();
}

/// <summary>
/// Launches the multithread worker
/// </summary>
/// <param name="rend">Renderer to use</param>
void Raytracer::RenderWorker(std::string filename) {
	progress = 0;
	lodepngReturn = -1;
	if (threadCount == -1)
		rendercycle(filename);
	else {
		worker = std::thread(Raytracer::rendercycle, filename);
		worker.detach();
		//while (progress != width)std::this_thread::sleep_for(std::chrono::milliseconds(100));//Sleep(100);
	}
}
void Raytracer::BlastImage(uint8_t** target) {
	TurboImage.blastGameImage(target);
}
void Raytracer::BlastImage(void* target) {
	TurboImage.blastGameImage(target);
}

void Raytracer::setsampleQuality(int samples) {
	if (renderer != nullptr)
		renderer.reset();
	if (samples <= 1)renderer = cam;
	else
		renderer = std::make_shared<cgSampling>(cgSampling(samples, cam));
}
#if SingleThread
void Raytracer::setPreviewThreadCount()noexcept {
	setSingleThread();
}

void Raytracer::setFullThreadCount()noexcept {
	setSingleThread();
}
#else
void Raytracer::setPreviewThreadCount() noexcept {
	threadCount = 1 + std::thread::hardware_concurrency() / 2;
}

void Raytracer::setFullThreadCount() noexcept {
	threadCount = std::thread::hardware_concurrency();
	//printf("Tc is now %d", threadCount);
}

#endif
void Raytracer::setSingleThread() noexcept {
	threadCount = 1;
}

void Raytracer::setThreadCount(int count) noexcept {
	if (count > 0)threadCount = count;
}

void Raytracer::abort() noexcept {
	abortRender = true;
	while (abortRender)Sleep(50);
}

void Raytracer::pauseRender(bool value) noexcept {
	pause = value;
}

void Raytracer::setPersistence(bool value) noexcept {

}
std::string restoreFile;
bool contains(std::string a, std::string b)noexcept {
	const auto al = a.length();
	const auto bl = b.length();
	if (bl > al)return false;
	else if (bl == al)return al == bl;
	const size_t m = al - bl + 1;
	for (size_t n = 0; n != m; n++) {
		size_t i = 0;
		while (i != bl && a[n + i] == b[i]) i++;
		if (i == bl)return true;
	}
	return false;
}
bool contains(std::wstring a, std::wstring b)noexcept {
	const auto al = a.length();
	const auto bl = b.length();
	if (bl > al)return false;
	else if (bl == al)return al == bl;
	const size_t m = al - bl + 1;
	for (size_t n = 0; n != m; n++) {
		size_t i = 0;
		while (i != bl && a[n + i] == b[i]) i++;
		if (i == bl)return true;
	}
	return false;
}
#if _WIN64
const std::filesystem::path::string_type backupfile = L"BACKUPFILE.BIN";
bool isRestoreFile(std::filesystem::path::string_type filename) {
	return contains(filename, backupfile);
}
#endif

bool Raytracer::hasRestoreFile() {
#if _WIN64
	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
		if (isRestoreFile(entry.path().filename()))
			return true;
	return false;
#else
	return false;
#endif
}
