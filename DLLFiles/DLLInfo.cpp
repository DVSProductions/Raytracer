#include <thread>
/// <summary>
/// Indicates whether the dll is doing stuff (not really required at this point)
/// </summary>
bool working = false;
/// <summary>
/// Main independent thread created by the dll. can do background tasks
/// </summary>
std::thread worker{};
/// <summary>
/// Shows the amount of columns rendered
/// </summary>
uint_fast32_t progress = 0;
/// <summary>
/// Return value of lodepng. -1 to unset
/// </summary>
int lodepngReturn = -1;
/// <summary>
/// Height and with of result
/// </summary>
uint_fast32_t width, height;
/// <summary>
/// Used to scale contents of the image
/// </summary>
int scaling = 1;
/// <summary>
/// keep at -1 to disable
/// </summary>
int_fast32_t progressOverride = -1;