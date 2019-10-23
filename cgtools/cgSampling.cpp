#include "cgSampling.h"
#include "DLLInfo.h"
cgSampling::cgSampling(uint16_t samples, Renderer* ActualRenderer) {
	child = ActualRenderer;
	this->samples = samples;
	//std::random_device rd;
	//mt = std::mt19937(rd());
	mt = std::mt19937(10);
	dist = std::uniform_real_distribution<double>(0, 1);
	samsq = static_cast<double>(static_cast<uint64_t>(samples)* static_cast<uint64_t>(samples));
}

Color cgSampling::getColor(double x, double y) noexcept{
#if DLL_DEBUG
	cout << "[GC";
#endif
	double resultsR = 0, resultsG = 0, resultsB = 0;
	for (int xi = 0; xi != samples; xi++) {
		for (int yi = 0; yi != samples; yi++) {
#if DLL_DEBUG
			cout << "->dist";
			double d1 = x + (xi + dist(mt)) / samples;
			double d2 = y + (yi + dist(mt)) / samples;
			cout << "->sampling";
			auto sample = child->getColor(d1, d2);
#else
			const auto sample = child->getColor(x + (xi + dist(mt)) / samples, y + (yi + dist(mt)) / samples);
#endif
			resultsR += sample.r;
			resultsG += sample.g;
			resultsB += sample.b;
		}
	}
	return Color(resultsR / samsq, resultsG / samsq, resultsB / samsq);
}

