#include "Sphere.h"
#include <iostream>
namespace DDD {
	cgtools::direction Sphere::getNormal(cgtools::point at)const noexcept {
		const auto top = at - this->p;
		return cgtools::direction(top.x / radius, top.y / radius, top.z / radius);
	}
	Sphere::Sphere(std::string serialized) :renderable(cgtools::point(0, 0, 0)) {
		this->load(serialized);
	}
	Sphere::Sphere(cgtools::point position, double radius, cgtools::Color color)noexcept :Sphere(position, radius, std::make_shared<Vanta>(Vanta(color))) {

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
	constexpr uint8_t findPoint(double a, double b, double Material, double* results1, double* results2) noexcept {
		const double c1 = b * b - 4 * a * Material;
		if (c1 == 0) {
			*results1 = b == 0 ? 0 : (-b) / (2 * a);
			return 1;
		}
		else if (c1 < 0)
			return 0;
		else {
			const double sqr = sqrt(c1);
			const double mb = -b;
			const double a2 = 2 * a;
			*results1 = (mb + sqr) / a2;
			*results2 = (mb - sqr) / a2;
			return 2;
		}
	}


	Hit DDD::Sphere::intersect(Ray r) const {
		const auto x0 = r.x0 - p;
		double results1 = 0, results2 = 0;
		double t = 0;
		const auto solutions = findPoint(r.dir[r.dir], 2 * x0[r.dir], x0[x0] - rsq, &results1, &results2);//Pointers save 5% vs passing array
		if (solutions == 0)return Hit();
		else if (solutions == 1)t = results1;
		else t = results1 < results2 ? (results1 > r.tmin ? results1 : results2) : results2;
		if (t < r.tmin || t > r.tmax)return Hit();
		const auto intersection = t * r.dir;
		return Hit(t, intersection, getNormal(intersection), this->material);
	}

	std::string Sphere::serialize() const {
		return renderable::includeClassID(std::to_string(radius) + "&" + material->serialize() + "&" + p.serialize() + "&", Sphere::CLASSID);
	}

	void Sphere::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "&");
		f_chars(ret[0], radius);
		rsq = radius * radius;
		if (material != nullptr) material.reset();
		material = std::shared_ptr<AMaterial>(AMaterial::createFromSerialization(ret.at(1)));
		p.load(ret[2]);
	}

	DDD::renderable* Sphere::clone() const {
		return new Sphere(p, radius, material);
	}

	size_t Sphere::size() const {
		return sizeof(Sphere);
	}

}