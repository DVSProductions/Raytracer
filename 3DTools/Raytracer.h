#pragma once
#include <thread>
#include <memory>
#include "Scene.h"
#include "ACamera.h"
#include "../3DDLL/3DInfo.h"
extern std::shared_ptr <DDD::Scene> playground;//=std::shared_ptr<DDD::Scene>();
extern std::shared_ptr <DDD::ACamera> cam; //= std::shared_ptr<DDD::ACamera>();s
namespace Raytracer {
	/// <summary>
	/// Generates the colors for every pixel and updates it's progress
	/// <para>
	/// Upgrade with version2: MULITHREADING</para>
	/// Yes this version of RenderLoop is designed to calculate every n-th line where n is the number of threads
	/// </summary>
	/// <param name="offset">my thread index</param>
	/// <param name="total">total number of threads</param>
	void RenderLoop(int offset, int total);
	/// <summary>
	/// Allocates memory and prepares, initializes and launches render threads
	/// </summary>
	/// <param name="filename">output filename</param>
	void rendercycle(std::string filename);
	/// <summary>
	/// Launches the multithread worker
	/// </summary>
	/// <param name="rend">Renderer to use</param>
	void RenderWorker(std::string filename);
	void setsampleQuality(int samples = 10);
	void setPreviewThreadCount() noexcept;
	void setFullThreadCount() noexcept;
	void setSingleThread() noexcept;
};
