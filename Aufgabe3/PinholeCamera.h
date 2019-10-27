#pragma once
#include "Camera.h"
/*
Tuple<double,double,double> calc(double w,double h,double a,double x,double y) {
. 	double w0_5 = w / 2.0;
. 	double h0_5 = h / 2.0;
. 	double a05tan = Math.Tan(a / 2.0);
. 	double zpre = -(w0_5 / a05tan);
. 	return new Tuple<double, double, double>(x - w0_5, h0_5 - y, zpre);
. }
. calc(10,10,Math.PI/2.0,0,0)*/

/// <summary>
/// Simulates a small pinhole camera
/// </summary>
class PinholeCamera :public Camera {
	double w0_5, h0_5;
	double a05tan;
	double zpre;
public:
	DDD::Ray generateRay(double x, double y);
	PinholeCamera(double angle, const point& position);
	Color getColor(double x, double y) override;
};

