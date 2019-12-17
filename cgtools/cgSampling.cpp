#include "cgSampling.h"
#include "../DLLFiles/DLLInfo.h"
namespace cgtools {
	//cgtools::cgSampling::cgSampling(short samples, std::unique_ptr<Renderer> ActualRenderer) noexcept {
	//	this->child.swap(ActualRenderer);
	//	this->samples = samples;
	//	//std::random_device rd;
	//	//mt = std::mt19937(rd());
	//	mt = std::mt19937(10);
	//	dist = std::uniform_real_distribution<double>(0, 1);
	//	samsq = static_cast<short>(samples)* static_cast<short>(samples);
	//}

	cgSampling::cgSampling(short samples, std::shared_ptr<Renderer> ActualRenderer) noexcept :dist(std::mt19937_64(std::random_device()())()) {
		this->child = ActualRenderer;
		if (samples < 1)samples = 1;
		this->samples = samples;
		samsq = static_cast<double>(samples)* static_cast<double>(samples);
	}

	Color cgSampling::getColor(double x, double y) {
#if DLL_DEBUG
		cout << "[GC";
#endif
		Color results;
		for (uint_fast32_t xi = 0; xi != samples; xi++) {
			for (uint_fast32_t yi = 0; yi != samples; yi++) {
#if DLL_DEBUG
				cout << "->dist";
				double d1 = x + (xi + dist()) / samples;
				double d2 = y + (yi + dist()) / samples;
				cout << "->sampling";
				auto sample = child->getColor(d1, d2);
				results += sample;
#else
				results += child->getColor(x + (xi + dist()) / samples, y + (yi + dist()) / samples);
#endif
			}
		}
		return results / samsq;// results / samsq;
	}
	std::shared_ptr<Renderer> cgSampling::clone() {
		return std::make_shared<cgSampling>(samples, child->clone());
	}
}