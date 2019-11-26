#include "cgSampling.h"
#include "DLLInfo.h"
using namespace cgtools;
//cgtools::cgSampling::cgSampling(short samples, std::unique_ptr<Renderer> ActualRenderer) noexcept {
//	this->child.swap(ActualRenderer);
//	this->samples = samples;
//	//std::random_device rd;
//	//mt = std::mt19937(rd());
//	mt = std::mt19937(10);
//	dist = std::uniform_real_distribution<double>(0, 1);
//	samsq = static_cast<short>(samples)* static_cast<short>(samples);
//}

cgtools::cgSampling::cgSampling(short samples, std::shared_ptr<Renderer> ActualRenderer) noexcept {
	this->child = ActualRenderer;
	if (samples < 1)samples = 1;
	this->samples = samples;
	std::random_device rd;
	mt = std::mt19937_64(rd());
	//mt = std::mt19937(10);
	dist = std::uniform_real_distribution<double>(0, 1);
	samsq = static_cast<int>(samples)* static_cast<int>(samples);
}

Color cgSampling::getColor(double x, double y) {
#if DLL_DEBUG
	cout << "[GC";
#endif
	Color results;
	for (int xi = 0; xi != samples; xi++) {
		for (int yi = 0; yi != samples; yi++) {
#if DLL_DEBUG
			cout << "->dist";
			double d1 = x + (xi + dist(mt)) / samples;
			double d2 = y + (yi + dist(mt)) / samples;
			cout << "->sampling";
			auto sample = child->getColor(d1, d2);
			results += sample;
#else
			results += child->getColor(x + (xi + dist(mt)) / samples, y + (yi + dist(mt)) / samples);
#endif
		}
	}
	return results / samsq;// results / samsq;
}

