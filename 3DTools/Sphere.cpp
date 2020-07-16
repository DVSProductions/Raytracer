#include "Sphere.h"
#include <iostream>
#include "Vanta.h"
namespace DDD {
	cgtools::direction Sphere::getNormal(cgtools::point at)const noexcept {
		return (at - p) / radius;
	}
	Sphere::Sphere(std::string serialized) :renderable(cgtools::point(0, 0, 0)) {
		this->load(serialized);
	}
	Sphere::Sphere(cgtools::point position, double radius, cgtools::Color color) : Sphere(position, radius, std::make_shared<Vanta>(Vanta(color))) {

	}
	Sphere::Sphere(cgtools::point position, double radius, std::shared_ptr<AMaterial>  mat) noexcept : renderable(position) {
		this->radius = radius;
		rsq = radius * radius;
		this->material = mat;
	}
	/// <summary>
	/// solves the equation. Using result pointers saves about 5% of render duration
	/// </summary>
	/// <returns></returns>
	//constexpr uint_fast8_t findPoint(double a, double b, double Material, double* results1, double* results2) noexcept {
	//	const double c1 = b * b - 4 * a * Material;
	//	if (c1 == 0) {
	//		*results1 = b == 0 ? 0 : (-b) / (2 * a);
	//		return 1;
	//	}
	//	else if (c1 < 0)
	//		return 0;
	//	else {
	//		const double a2 = 2 * a;
	//		const double sqr = sqrt(c1);
	//		const double mb = -b;
	//		*results1 = (mb + sqr) / a2;
	//		*results2 = (mb - sqr) / a2;
	//		return 2;
	//	}
	//}
	//#define findPointMacro(ret,a,b,Material,results1,results2) const double c1 = b * b - 4 * a * Material;\
	//	if (c1 == 0) {\
	//		results1 = b == 0 ? 0 : (-b) / (2 * a);\
	//		ret= 1;\
	//	}\
	//	else if (c1 < 0)\
	//		ret= 0;\
	//	else {\
	//		const double a2 = 2 * a;\
	//		const double sqr = sqrt(c1);\
	//		const double mb = -b;\
	//		results1 = (mb + sqr) / a2;\
	//		results2 = (mb - sqr) / a2;\
	//		ret= 2;\
	//	}

	//Hit Sphere::intersect(Ray r) const noexcept {
	//	const auto x0 = r.x0 - p;
	//	double results1 = 0, results2 = 0;
	//	double t = 0;
	//	uint_fast8_t resultcount = 0;
	//	/*findPointMacro(resultcount, r.dir[r.dir], x0[r.dir] * 2, x0[x0] - rsq, results1, results2);
	//	switch (resultcount) {*/
	//	switch (findPoint(r.dir[r.dir], x0[r.dir] * 2, x0[x0] - rsq, &results1, &results2)) {//Pointers save 5% vs passing array
	//	case 1:
	//		t = results1;
	//		break;
	//	case 2:
	//		if (results1 < results2) {//r1 is smaller
	//			if (results1 > r.tmin)//and within bounds
	//				t = results1;
	//			else t = results2;//outside of min bound? try r2
	//		}
	//		else {//r2 is smaller
	//			if (results2 > r.tmin)//and within bounds
	//				t = results2;
	//			else t = results1;//outside of min bound? try r1
	//		}
	//		break;
	//	default:
	//		return Hit();
	//	}
	//	if (t < r.tmin || t > r.tmax)
	//		return Hit();
	//	const auto intersection = r.getPoint(t);
	//	return Hit(t, intersection, getNormal(intersection), this->material);
	//}
	Hit Sphere::intersect(Ray r) const noexcept {
		double t = 0, results1=0, results2=0, mb=0;
		const auto x0 = r.x0 - p;
		const double
			a = r.dir[r.dir],
			b = x0[r.dir] * 2,
			c1 = b * b - 4 * a * (x0[x0] - rsq);
		
		if (c1 == 0)
			t = b == 0 ? 0 : (-b) / (2 * a);
		else if (c1 < 0)
			return Hit();
		else {
			mb = -b;
			results1 = (mb + sqrt(c1)) / (2 * a);
			results2 = (mb - sqrt(c1)) / (2 * a);
			if (results1 < results2) {//r1 is smaller
				if (results1 > r.tmin)//and within bounds
					t = results1;
				else t = results2;//outside of min bound? try r2
			}
			else {//r2 is smaller
				if (results2 > r.tmin)//and within bounds
					t = results2;
				else t = results1;//outside of min bound? try r1
			}
		}
		if (t < r.tmin || t > r.tmax)
			return Hit();
		const auto intersection = r.getPoint(t);
		return Hit(t, intersection, getNormal(intersection), this->material);
	}

	std::string Sphere::serialize() const {
		return includeClassID(std::to_string(radius) + "&" + material->serialize() + "&" + p.serialize() + "&", CLASSID);
	}

	void Sphere::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "&");
		f_chars(ret.at(0), radius);
		rsq = radius * radius;
		if (material != nullptr) material.reset();
		material = std::shared_ptr<AMaterial>(AMaterial::createFromSerialization(ret.at(1)));
		p.load(ret.at(2));
	}

	renderable* Sphere::clone() const {
		return new Sphere(p, radius, material);
	}

	size_t Sphere::size() const noexcept {
		return sizeof(Sphere);
	}

}