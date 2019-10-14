#pragma once
#include <thread>
#include <string>
/// <summary>
/// Contains all file options and a "_" at the end to signal the end of list
/// </summary>
const std::string files[] = { "a01-image.png","a01-square.png","a01-checkered-background.png","_" };
extern bool working;
extern std::thread worker;
/// <summary>
/// 0-1000
/// </summary>
extern int progress;
extern int lodepngReturn;
extern int width, height;
