#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <direct.h>
#include <Windows.h>
#include <vector>
#include <functional>
#include <memory>
//#include "CacheCow.h"
#include "../3DTools/Raytracer.h"

#include "../3DDLL/3DInfo.h"
#include "../3DTools/Scene.h"
#include "../3DTools/ACamera.h"
#include "../DLLFiles/DLLInfo.h"
#include "../cgtools/cgtools.h"
#include "../cgtools/cgSampling.h"
#include "../cgtools/Image.h"
#include "../3DTools/PinholeCamera.h"
#include "../3DTools/Sphere.h"
#include "../3DTools/Plane.h"

/// <summary>
/// -1 terminated array of Supported Element classes
/// </summary>
const std::string files[] = { "a04-3-spheres.png","a04-scene.png","_" };
const std::string libVersion = "2.1";

void prepare() {
	if (playground != nullptr)
		playground->clear();
	playground = std::make_shared <DDD::Scene>();
	//Playground->addObject(new Sphere(point(100, 100, 100), 50, c_red));
	const Color gray = Color::fromRGB(60, 60, 60).reverseGamma(2.2);//application background color
	const Color red = Color::fromRGB(0x9B, 0x55, 0x55).reverseGamma(2.2);//application default red color
	const Color b = Color(0, 0, 1);
	cam = std::make_shared <DDD::PinholeCamera>(DDD::PinholeCamera(M_PI / 3, DDD::Background(gray)));
	cam->setScene(playground);
	Raytracer::setsampleQuality();
}

void loadSpheres() {
	playground->addObject(new DDD::Plane(cgtools::point(0.0, -0.5, 0.0), cgtools::direction(0, 1, 0), cgtools::c_gray));
	playground->addObject(new DDD::Sphere(cgtools::point(-1.0, -0.25, -2.5), 0.7, cgtools::c_red));
	playground->addObject(new DDD::Sphere(cgtools::point(0.0, -0.25, -2.5), 0.5, cgtools::c_green));
	playground->addObject(new DDD::Sphere(cgtools::point(1.0, -0.25, -2.5), 0.7, cgtools::c_blue));
}

std::string KirbyWithBG = "0!1&1|0.615686274509804|0.815686274509804|&0|0|-20|&!$0!0.5&0.866666666666667|0.0745098039215686|0.301960784313725|&-0.5|-1|-20|&!$0!0.5&0.866666666666667|0.0745098039215686|0.301960784313725|&0.7|-0.7|-21|&!$0!0.3&0.996078431372549|0.63921568627451|0.831372549019608|&-0.9|0|-19.5|&!$0!0.3&0.996078431372549|0.63921568627451|0.831372549019608|&1|0.4|-20|&!$0!0.1&1|1|1|&-0.06|0.2|-18.96|&!$0!0.1&1|1|1|&0.4|0.3|-18.99|&!$1!0.2&0.8|0.25|1|&0.0431372549019608|0.0431372549019608|0.0823529411764706|&-0.05|0.15|-19|&!$1!0.2&-0.8|-0.25|1|&0.0431372549019608|0.0431372549019608|0.0823529411764706|&-0.05|0.15|-19|&!$1!0.2&1|0.3|1|&0.0431372549019608|0.0431372549019608|0.0823529411764706|&0.43|0.26|-19|&!$1!0.3&0|1|1.5|&0.458823529411765|0.0235294117647059|0.0666666666666667|&0.2|-0.2|-19|&!$0!0.2&0.996078431372549|0.411764705882353|0.729411764705882|&-0.3|-0.06|-19.22|&!$0!0.18&0.996078431372549|0.411764705882353|0.729411764705882|&0.65|0.17|-19.46|&!$0!75&0.674509803921569|0.894117647058824|1|&-20|-20|-200|&!$1!5&0|1|0|&0.423529411764706|0.76078431372549|0.870588235294118|&0|-1.4|-20|&!$1!1.5&0|1|0|&0.168627450980392|0.6|0.741176470588235|&-0.7|-1.3999999|-20.4|&!$1!0.6&0|1|0|&0.141176470588235|0.501960784313725|0.615686274509804|&-0.8|-1.39998|-20.4|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-4|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-3|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-2|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-1|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&0|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&1|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&2|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&3|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&4|2|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-4|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-3|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-2|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-1|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&0|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&1|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&2|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&3|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&4|1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-4|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-3|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-2|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-1|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&0|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&1|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&2|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&3|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&4|0|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-4|-1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-3|-1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-2|-1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&-1|-1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&0|-1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&1|-1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&2|-1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&3|-1|-30|&!$0!0.2&0.611764705882353|0.835294117647059|0.92156862745098|&4|-1|-30|&!$";
std::string KirbiesCamera = "0!0.576470588235294|0.823529411764706|0.823529411764706|[0.3&0|0|0|&[!";
void loadMine() {
	prepare3d();
	playground->load(KirbyWithBG);
	auto sh = DDD::ACamera::createFromSerialization(KirbiesCamera);
	if (cam != nullptr) {
		cam.reset();
		cam.swap(sh);
	}
	else
		cam = sh;
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
	prepare();
	switch (Option) {
	case 0:
		loadSpheres();
		break;
	case 1:
		loadMine();
		break;
	default:
		return false;
	}
	Raytracer::setFullThreadCount();
	Raytracer::RenderWorker(files[Option]);
	return true;
}



//-----------------------------------------------------------------------------
//3D scene Functions
const int supportedClasses[] = { 0,1,2,-1 };
const int supportedCams[] = { 0,-1 };
const int supportedMaterials[] = { 0,2,-1 };
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
	Raytracer::setsampleQuality(5);
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
