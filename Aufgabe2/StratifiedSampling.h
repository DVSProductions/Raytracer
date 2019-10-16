#pragma once
#include "Renderer.h"
#include <random>
class StratifiedSampling : public Renderer {
	int samples;
	Renderer* child;
	std::mt19937 mt;
	std::uniform_real_distribution<double> dist;
public:
	StratifiedSampling(int samples, Renderer* ActualRenderer);
	Color getColor(double x, double y);
};

