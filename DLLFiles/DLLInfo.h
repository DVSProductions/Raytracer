#pragma once
#define DLL_DEBUG false
#if DLL_DEBUG
#include <iostream>
#include <Windows.h>
using namespace std;
#endif
#include <thread>
#include <string>
/// <summary>
/// Contains all file options and a "_" at the end to signal the end of list
/// <para>
/// Define this in your DLL</para>
/// </summary>
extern const std::string files[];// = { "a01-image.png","a01-square.png","a01-checkered-background.png","_" };
extern const std::string libVersion;
/// <summary>
/// Indicates whethers the dll is doing stuff (not really required at this point)
/// </summary>
extern bool working;
/// <summary>
/// Main independent thread created by the dll. can do background tasks
/// </summary>
extern std::thread worker;
/// <summary>
/// Shows the amount of columns rendered
/// </summary>
extern int progress;
/// <summary>
/// Return value of lodepng. -1 to unset
/// </summary>
extern int lodepngReturn;
/// <summary>
/// Height and with of result
/// </summary>
extern int width, height;
/// <summary>
/// Used to scale contents of the image
/// </summary>
extern int scaling;
