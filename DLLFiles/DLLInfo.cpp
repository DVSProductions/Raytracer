#include <thread>
bool working = false;
std::thread worker;
/// <summary>
/// 0- width
/// </summary>
int progress = 0;
int lodepngReturn = -1;

int width, height;
int scaling = 1;