#pragma once
#include <Scene.h>
#include <ACamera.h>
/// <summary>
/// -1 terminated
/// </summary>
extern int supportedClasses[];
extern std::shared_ptr<DDD::Scene> playground;
extern std::shared_ptr <DDD::ACamera> cam;
extern void prepare3d();