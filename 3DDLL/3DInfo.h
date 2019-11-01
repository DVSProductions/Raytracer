#pragma once
#include <memory>
#include <../3DTools/Scene.h>
#include <../3DTools/ACamera.h>
/// <summary>
/// -1 terminated
/// </summary>
extern const int supportedClasses[];
extern std::shared_ptr <DDD::Scene> playground;
extern std::shared_ptr <DDD::ACamera> cam;
extern void prepare3d();