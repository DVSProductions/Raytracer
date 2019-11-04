#pragma once
#include <memory>
#include <../3DTools/Scene.h>
#include <../3DTools/ACamera.h>
/// <summary>
/// -1 terminated
/// </summary>
extern const int supportedClasses[];
extern const int supportedCams[];
extern std::shared_ptr <DDD::Scene> playground;
extern std::shared_ptr <DDD::ACamera> cam;
extern const std::string sceneOutputFile;
extern void prepare3d();
extern void renderScene(int x,int y);