#pragma once
#include "../cgtools/point.h"
#include "Hit.h"
#include "Ray.h"
namespace DDD {
	class renderable {
	protected:

		renderable(cgtools::point position);
	public:
		const cgtools::point p;
		virtual Hit* intersect(Ray r) = 0;
	};
}
