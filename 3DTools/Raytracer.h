#pragma once
#include <thread>
#include <memory>
#include "Scene.h"
#include "ACamera.h"
#include "GameCamera.h"
#include "../3DDLL/3DInfo.h"
extern std::shared_ptr <DDD::Scene> playground;
extern std::shared_ptr <DDD::ACamera> cam; 
extern std::shared_ptr <DDD::GameCamera> gameCam;
namespace Raytracer {
	/// <summary>
	/// Generates the colors for every pixel and updates it's progress
	/// <para>
	/// Upgrade with version2: MULITHREADING</para>
	/// Yes this version of RenderLoop is designed to calculate every n-th line where n is the number of threads
	/// </summary>
	/// <param name="offset">my thread index</param>
	/// <param name="total">total number of threads</param>
	void RenderLoop(uint_fast32_t offset, uint_fast32_t total, std::shared_ptr<cgtools::Renderer> target);
	/// <summary>
	/// Allocates memory and prepares, initializes and launches render threads
	/// </summary>
	/// <param name="filename">output filename</param>
	void rendercycle(std::string filename);
	void TurboRenderLoop(uint_fast32_t offset, uint_fast32_t total, std::shared_ptr<cgtools::Renderer> target);
	void turboRendercycle(double gamma);
	void prepareTurboRender(int FSAA, int threads);
	void turboRender(int x, int y, double gamma);
	/// <summary>
	/// Launches the multithread worker
	/// </summary>
	/// <param name="rend">Renderer to use</param>
	void RenderWorker(std::string filename);
	void BlastImage(uint8_t** target);
	void BlastImage(void* target);
	void setsampleQuality(int samples = 10);
	void setPreviewThreadCount() noexcept;
	void setFullThreadCount() noexcept;
	void setSingleThread() noexcept;
	void setThreadCount(int count)noexcept;
	void abort() noexcept;
	void pauseRender(bool value) noexcept;
	void setPersistence(bool value)noexcept;
	bool hasRestoreFile();
};
