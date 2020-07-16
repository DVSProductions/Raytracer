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
#include "../3DTools/Scene.h"
#include "GraphRoot.h"
extern std::shared_ptr <DDD::GraphRoot> SceneGraph;
extern const int supportedGenerators[];