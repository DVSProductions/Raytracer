#pragma once
#include <Color.h>
#include <point.h>
using namespace cgtools;
struct Hit {
	double t;
	point pos;
	direction n;
	Color c;
};

