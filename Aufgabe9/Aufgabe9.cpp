#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <direct.h>
#include <vector>
#include <functional>
#include <memory>
#include <thread>
#include <fstream>
//#include "CacheCow.h"
#include "Raytracer.h"

#include "DLLTransforms.h"
#include "3DInfo.h"
#include "Scene.h"
#include "ACamera.h"
#include "DllInfo.h"
#include "cgtools.h"
#include "Image.h"
#include "cgSampling.h"
#include "PinholeCamera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Chalk.h"
using namespace DDD;

/// <summary>
/// -1 terminated array of Supported Element classes
/// </summary>
const std::string files[] = { "a09-benchmark-scene.png","a09-results_graph.png","_" };
const std::string libVersion = "3";
//std::string GlassDemo = "1!-1&0|1|0|&2#0.705882352941177|0.705882352941177|0.705882352941177|}0.00392156862745098|0.00392156862745098|0.00392156862745098|}#&0|-1|0|&!$0!0.4&5#1.5}0.95|0.95|0.95|}0|0|0|}#&0|0|-3|&!$0!1&2#0.901960784313726|0.101960784313725|0.8|}0.0313725490196078|0.0313725490196078|0.0313725490196078|}#&-7|0|-7|&!$0!1&2#1|0|0|}0|0|0|}#&-5|0|-7|&!$0!1&2#1|0.850980392156863|0|}0.0117647058823529|0.0117647058823529|0.0117647058823529|}#&-3|0|-7|&!$0!1&2#0.301960784313725|1|0|}0.00392156862745098|0.00392156862745098|0.00392156862745098|}#&-1|0|-7|&!$0!1&2#0|1|0.549019607843137|}0|0|0|}#&1|0|-7|&!$0!1&2#0|0.576470588235294|1|}0|0|0|}#&3|0|-7|&!$0!1&2#0.274509803921569|0|1|}0|0|0|}#&5|0|-7|&!$0!1&2#0.901960784313726|0.101960784313725|0.8|}0.0313725490196078|0.0313725490196078|0.0313725490196078|}#&7|0|-7|&!$0!1&2#1|0|0|}0|0|0|}#&9|0|-7|&!$0!0.3&5#1}0.95|0.95|0.95|}0|0|0|}#&-3|-0.7|-3|&!$0!0.3&5#1.1}0.95|0.95|0.95|}0|0|0|}#&-2.3|-0.7|-3|&!$0!0.3&5#1.2}0.95|0.95|0.95|}0|0|0|}#&-1.6|-0.7|-3|&!$0!0.3&5#1.4}0.95|0.95|0.95|}0|0|0|}#&-0.9|-0.7|-3|&!$0!0.3&5#1.5}0.95|0.95|0.95|}0|0|0|}#&-0.2|-0.7|-3|&!$0!0.3&5#1.6}0.95|0.95|0.95|}0|0|0|}#&0.5|-0.7|-3|&!$0!0.3&5#1.7}0.95|0.95|0.95|}0|0|0|}#&1.2|-0.7|-3|&!$0!0.3&5#1.8}0.95|0.95|0.95|}0|0|0|}#&1.9|-0.7|-3|&!$0!0.3&5#1.9}0.95|0.95|0.95|}0|0|0|}#&2.6|-0.7|-3|&!$0!0.3&5#2}0.95|0.95|0.95|}0|0|0|}#&3.3|-0.7|-3|&!$0!5&1|1|1|&0|0|5|&!$";
std::string GlassDemo = "1!-1&0|1|0|&2#0.705882352941177|0.705882352941177|0.705882352941177|}0.00392156862745098|0.00392156862745098|0.00392156862745098|}#&0|-1|0|&!$0!0.4&5#1.5}0.95|0.95|0.95|}0|0|0|}#&0|0|-3|&!$0!1&2#0.901960784313726|0.101960784313725|0.8|}0.0313725490196078|0.0313725490196078|0.0313725490196078|}#&-7|0|-7|&!$0!1&2#1|0|0|}0|0|0|}#&-5|0|-7|&!$0!1&2#1|0.850980392156863|0|}0.0117647058823529|0.0117647058823529|0.0117647058823529|}#&-3|0|-7|&!$0!1&2#0.301960784313725|1|0|}0.00392156862745098|0.00392156862745098|0.00392156862745098|}#&-1|0|-7|&!$0!1&2#0|1|0.549019607843137|}0|0|0|}#&1|0|-7|&!$0!1&2#0|0.576470588235294|1|}0|0|0|}#&3|0|-7|&!$0!1&2#0.274509803921569|0|1|}0|0|0|}#&5|0|-7|&!$0!1&2#0.901960784313726|0.101960784313725|0.8|}0.0313725490196078|0.0313725490196078|0.0313725490196078|}#&7|0|-7|&!$0!1&2#1|0|0|}0|0|0|}#&9|0|-7|&!$0!0.3&5#1}0.95|0.95|0.95|}0|0|0|}#&-3|-0.7|-3|&!$0!0.3&5#1.1}0.95|0.95|0.95|}0|0|0|}#&-2.3|-0.7|-3|&!$0!0.3&5#1.2}0.95|0.95|0.95|}0|0|0|}#&-1.6|-0.7|-3|&!$0!0.3&5#1.4}0.95|0.95|0.95|}0|0|0|}#&-0.9|-0.7|-3|&!$0!0.3&5#1.5}0.95|0.95|0.95|}0|0|0|}#&-0.2|-0.7|-3|&!$0!0.3&5#1.6}0.95|0.95|0.95|}0|0|0|}#&0.5|-0.7|-3|&!$0!0.3&5#1.7}0.95|0.95|0.95|}0|0|0|}#&1.2|-0.7|-3|&!$0!0.3&5#1.8}0.95|0.95|0.95|}0|0|0|}#&1.9|-0.7|-3|&!$0!0.3&5#1.9}0.95|0.95|0.95|}0|0|0|}#&2.6|-0.7|-3|&!$0!0.3&5#2}0.95|0.95|0.95|}0|0|0|}#&3.3|-0.7|-3|&!$";
std::string GlassDemoCamera = "0!1|1|1|[1.7&0|0|0|&150&[!";
void loadGlass() {
	prepare3d();
	playground->load(GlassDemo);
	auto sh = DDD::ACamera::createFromSerialization(GlassDemoCamera);
	if (cam != nullptr) {
		cam.reset();
		cam.swap(sh);
	}
	else
		cam = sh;
	cam->init();
	cam->setScene(playground);
}

void benchmark() {
	
	int tc = std::thread::hardware_concurrency();
	std::vector<long long> durations;
	progressOverride = 0;
	for (int n = 0; n != tc; n++) {
		loadGlass();
		progress = 0;
		Raytracer::setsampleQuality(10);
		Raytracer::setThreadCount(n+1);
		auto start = std::chrono::system_clock::now();
		Raytracer::RenderWorker("tmp");
		while (progress != width) {
			auto v = (n * width + progress) / tc;
			if (v > 10)v -= 10;
			progressOverride = v;
			Sleep(10);
		}
		auto dur = std::chrono::system_clock::now() - start;
		durations.push_back(dur.count());
		while (lodepngReturn == -1)Sleep(10);
	}
	std::ofstream resultfile("results.csv");
	resultfile << "Threadcount;Duration" << std::endl;
	long long max = 0;
	for (int n = 0; n != durations.size(); n++) {
		if (durations[n] > max)max = durations[n];
		resultfile << n+1 << ";" << durations[n] << std::endl;
	}
	resultfile.close();
	prepare3d();
	playground->clear();
	playground->addObject(new Plane(cgtools::point(0,-1,0),cgtools::direction(0,1,0),std::make_shared<Chalk>(
		cgtools::c_black, cgtools::Color(0.75,0.75,0.75))));
	double w = 2;
	for (int n = 0; n != durations.size(); n++) {
		playground->addObject(new Cylinder(cgtools::point(
			(w * ((double)n / ((double)durations.size()-1))) - (w/2), -0.5, -1),
			w / (tc+5),
			((long double)durations[n]/(long double)max) * 4.2,
			std::make_shared<Chalk>(cgtools::c_black, cgtools::Color::getRandom(std::mt19937_64(std::random_device()())))
		));
	}
	width *= 10;
	height *= 10;
	auto sh = DDD::ACamera::createFromSerialization(GlassDemoCamera);
	if (cam != nullptr) {
		cam.reset();
		cam.swap(sh);
	}
	else
		cam = sh;
	cam->init();
	cam->setScene(playground);
	
	Raytracer::setsampleQuality(20);
	Raytracer::setFullThreadCount();
	Raytracer::RenderWorker(files[1]);
	remove("tmp");
	while (progress != width) {
		progressOverride = progress / 10;
		Sleep(30);
	}
	while (lodepngReturn == -1)Sleep(100);
	progressOverride = -1;
}

/// <summary>
/// Decides which File to render and with what options
/// </summary>
/// <param name="Option">index of file</param>
bool workswitch(int Option) {
#if DLL_DEBUG
	cout << "WS" << endl;
#endif
	//prepare();
	switch (Option) {
	case 0:
		loadGlass();
		Raytracer::setsampleQuality(10);
		Raytracer::setFullThreadCount();
		Raytracer::RenderWorker(files[Option]);
		break;
	case 1:
		std::thread(benchmark).detach();
		break;
	default:
		return false;
	}
	return true;
}



//-------------------------------------------------------------------------------------------------------------
//3D scene Functions
const int supportedClasses[] = { 0,1,2,3,4,			-1 };
const int supportedCams[] = { 0,1,					-1 };
const int supportedMaterials[] = { 0,1,2,3,4,5,		-1 };
const int supportedTransforms[] = { 0,1,2,3,		-1 };
const std::string sceneOutputFile = "sof.png";

void prepare3d() {
	if (playground != nullptr)playground.reset();
	playground = std::make_shared<DDD::Scene>();
}

void renderPreview(int x, int y) {
	width = x;
	height = y;
	cam->init();
	cam->setScene(playground);
	Raytracer::setsampleQuality(0);
	Raytracer::setPreviewThreadCount();
	Raytracer::RenderWorker(sceneOutputFile);
}
void renderScene(int x, int y, int FSAA, std::string outputFilePath) {
	width = x;
	height = y;
	cam->init();
	cam->setScene(playground);
	Raytracer::setsampleQuality(FSAA);
	Raytracer::setFullThreadCount();
	Raytracer::RenderWorker(outputFilePath);
}
void abortRender() {
	Raytracer::abort();
}