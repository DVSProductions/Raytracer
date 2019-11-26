#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <direct.h>
#include <Windows.h>
#include <vector>
#include <functional>
#include <memory>
//#include "CacheCow.h"
#include "Raytracer.h"

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

/// <summary>
/// -1 terminated array of Supported Element classes
/// </summary>
const std::string files[] = { "a06-mirrors-glass-1.png","a06-mirrors-glass-2.png","_" };
const std::string libVersion = "2.1";

void prepare() {
	if (playground != nullptr)
		playground->clear();
	playground = std::make_shared <DDD::Scene>();
	//Playground->addObject(new Sphere(point(100, 100, 100), 50, c_red));
	const Color gray = Color::fromRGB(60, 60, 60).reverseGamma(2.2);//application background color
	const Color red = Color::fromRGB(0x9B, 0x55, 0x55).reverseGamma(2.2);//application default red color
	const Color b = Color(0, 0, 1);
	cam = std::make_shared <DDD::PinholeCamera>(DDD::PinholeCamera(M_PI / 3, cgtools::point(0, 0, 0), DDD::Background(gray)));
	cam->setScene(playground);
	Raytracer::setsampleQuality();
}

std::string Room = "1!-1&0|1|0|&2#0.9|0.9|0.9|}0|0|0|}#&0|-1|0|&!$0!0.7&1#0.95|0.95|0.95|}0|0|0|}#&-1.2|-0.3|-2.5|&!$0!0.7&2#0|0|0.768627450980392|}0|0|0|}#&1.2|-0.5|-6|&!$0!0.7&2#0|0.701960784313725|0.701960784313725|}0|0|0|}#&-2|-1.1|0|&!$0!0.5&4#0.1}0.788235294117647|0.788235294117647|0.788235294117647|}0.0196078431372549|0.0196078431372549|0.0196078431372549|}#&0|0|-4|&!$1!-1&-1|0|0|&1#0.831372549019608|0.831372549019608|0.831372549019608|}0|0|0|}#&3|0|0|&!$1!-1&1|0|0|&1#0.831372549019608|0.831372549019608|0.831372549019608|}0|0|0|}#&-3|0|0|&!$1!-1&0|-0.05|1|&4#0.01}0.831372549019608|0.831372549019608|0.831372549019608|}0|0|0|}#&0|0|-10|&!$1!-1&0|0.05|-1|&4#0.01}0.831372549019608|0.831372549019608|0.831372549019608|}0|0|0|}#&0|0|4|&!$1!-1&0|-1|0|&2#0.9|0.9|0.9|}0|0|0|}#&0|4|0|&!$0!1&3#1|0.168627450980392|0.168627450980392|#&-3|3.5|-1|&!$0!1&0.168627450980392|0.207843137254902|1|&3|3.5|-1|&!$1!1&0|1|0|&3#0.705882352941177|0.705882352941177|0.705882352941177|#&0|-0.99999|-9|&!$1!0.5&0|1|0|&3#1.24705882352941|1.24705882352941|1.24705882352941|#&0|-0.9999|3.5|&!$0!0.3&4#0.4}1|1|1|}0.592156862745098|0.592156862745098|0|}#&2|0|-3|&!$0!1&4#0.5}1|0.843137254901961|0|}0|0|0|}#&2|-1|-4|&!$";
std::string RoomCamera = "0!0.423529411764706|0.423529411764706|0.423529411764706|[1.5707963267949&0|0|0|&10&[!";
void loadRoom() {
	prepare3d();
	playground->load(Room);
	auto sh = DDD::ACamera::createFromSerialization(RoomCamera);
	if (cam != nullptr) {
		cam.reset();
		cam.swap(sh);
	}
	else
		cam = sh;
	cam->init();
	cam->setScene(playground);
}
std::string GlassDemo = "1!-1&0|1|0|&2#0.705882352941177|0.705882352941177|0.705882352941177|}0.00392156862745098|0.00392156862745098|0.00392156862745098|}#&0|-1|0|&!$0!0.4&5#1.5}0.95|0.95|0.95|}0|0|0|}#&0|0|-3|&!$0!1&2#0.901960784313726|0.101960784313725|0.8|}0.0313725490196078|0.0313725490196078|0.0313725490196078|}#&-7|0|-7|&!$0!1&2#1|0|0|}0|0|0|}#&-5|0|-7|&!$0!1&2#1|0.850980392156863|0|}0.0117647058823529|0.0117647058823529|0.0117647058823529|}#&-3|0|-7|&!$0!1&2#0.301960784313725|1|0|}0.00392156862745098|0.00392156862745098|0.00392156862745098|}#&-1|0|-7|&!$0!1&2#0|1|0.549019607843137|}0|0|0|}#&1|0|-7|&!$0!1&2#0|0.576470588235294|1|}0|0|0|}#&3|0|-7|&!$0!1&2#0.274509803921569|0|1|}0|0|0|}#&5|0|-7|&!$0!1&2#0.901960784313726|0.101960784313725|0.8|}0.0313725490196078|0.0313725490196078|0.0313725490196078|}#&7|0|-7|&!$0!1&2#1|0|0|}0|0|0|}#&9|0|-7|&!$0!0.3&5#1}0.95|0.95|0.95|}0|0|0|}#&-3|-0.7|-3|&!$0!0.3&5#1.1}0.95|0.95|0.95|}0|0|0|}#&-2.3|-0.7|-3|&!$0!0.3&5#1.2}0.95|0.95|0.95|}0|0|0|}#&-1.6|-0.7|-3|&!$0!0.3&5#1.4}0.95|0.95|0.95|}0|0|0|}#&-0.9|-0.7|-3|&!$0!0.3&5#1.5}0.95|0.95|0.95|}0|0|0|}#&-0.2|-0.7|-3|&!$0!0.3&5#1.6}0.95|0.95|0.95|}0|0|0|}#&0.5|-0.7|-3|&!$0!0.3&5#1.7}0.95|0.95|0.95|}0|0|0|}#&1.2|-0.7|-3|&!$0!0.3&5#1.8}0.95|0.95|0.95|}0|0|0|}#&1.9|-0.7|-3|&!$0!0.3&5#1.9}0.95|0.95|0.95|}0|0|0|}#&2.6|-0.7|-3|&!$0!0.3&5#2}0.95|0.95|0.95|}0|0|0|}#&3.3|-0.7|-3|&!$0!5&1|1|1|&0|0|5|&!$";
std::string GlassDemoCamera = "0!1|1|1|[1.7&0|0|0|&100&[!";
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
		loadRoom();
		break;
	case 1:
		loadGlass();
		break;
	default:
		return false;
	}
	Raytracer::setsampleQuality(10);
	Raytracer::setFullThreadCount();
	Raytracer::RenderWorker(files[Option]);
	return true;
}



//-----------------------------------------------------------------------------
//3D scene Functions
const int supportedClasses[] = { 0,1,2,-1 };
const int supportedCams[] = { 0,-1 };
const int supportedMaterials[] = { 0,1,2,3,4,5, -1 };
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