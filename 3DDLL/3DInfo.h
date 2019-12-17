#pragma once
#ifdef _WIN64 
#define dll(x) __declspec(dllexport) x __cdecl
#include <comutil.h>
#else
#define EXTERN_C_START
#define EXTERN_C_END
#define dll(x) x
#define BSTR char*
#endif
#include <memory>
#include <../3DTools/Scene.h>
#include <../3DTools/ACamera.h>
/// <summary>
/// -1 terminated
/// </summary>
extern const int supportedClasses[];
extern const int supportedCams[];
extern const int supportedMaterials[];
extern std::shared_ptr <DDD::Scene> playground;
extern std::shared_ptr <DDD::ACamera> cam;
extern const std::string sceneOutputFile;
extern void prepare3d();
extern void renderPreview(int x,int y);
extern void renderScene(int x,int y,int FSAA,std::string outputFilePath);