#include "Pipe.h"
namespace DDD {
	Pipe::Pipe(std::string serialized):renderable(cgtools::point(0,0,0)) {
		load(serialized);
	}
	Pipe::Pipe(cgtools::point position, double radius, double height, std::shared_ptr<AMaterial> mat) noexcept :renderable(position), radius(radius), rsq(radius* radius),height(height) {
		material = mat;
	}

	/// <summary>
	/// solves the equation. Using result pointers saves about 5% of render duration
	/// </summary>
	/// <returns></returns>
	constexpr uint_fast8_t findPoint(double a, double b, double Material, double* results1, double* results2) noexcept {
		const double c1 = b * b - 4 * a * Material;
		if (c1 == 0) {
			*results1 = b == 0 ? 0 : (-b) / (2 * a);
			return 1;
		}
		else if (c1 < 0)
			return 0;
		else {
			const double a2 = 2 * a;
			const double sqr = sqrt(c1);
			const double mb = -b;
			*results1 = (mb + sqr) / a2;
			*results2 = (mb - sqr) / a2;
			return 2;
		}
	}

	Hit Pipe::intersect(Ray r) const noexcept {
		const auto x0s = cgtools::point(r.x0.x - p.x, 0, r.x0.z - p.z);
		const auto directCenter = cgtools::direction(p.x, 0, p.z);
		const auto x0c = cgtools::point(r.x0.x, 0, r.x0.z) - directCenter;
		double results1 = 0, results2 = 0;
		double t = 0;
		switch (findPoint(r.dir.x * r.dir.x + r.dir.z * r.dir.z, (2 * r.dir.x * x0s.x) + (2 * r.dir.z * x0s.z), (x0s.x * x0s.x) + (x0s.z * x0s.z) - (radius * radius), &results1, &results2)) {
		case 1:
			t = results1;
			break;
		case 2:
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
			break;
		default:
			return Hit();
		}
		if (t < r.tmin || t > r.tmax)
			return Hit();
		const auto intersection = r.getPoint(t);
		return (intersection.y > (p.y - height / 2) && intersection.y < ((p.y + height / 2))) ?
			Hit(t, intersection, ~cgtools::direction(intersection.x - p.x, 0, intersection.z - p.z), material) :
			Hit();
	}

	std::string Pipe::serialize() const {
		return includeClassID(std::to_string(radius) + "&" + std::to_string(height) + "&" + material->serialize() + "&" + p.serialize() + "&", CLASSID);
	}

	void Pipe::load(std::string serialized) {
		auto ret = Serializable::split(serialized, "&");
		f_chars(ret.at(0), radius);
		f_chars(ret.at(1), height);
		rsq = radius * radius;
		if (material != nullptr) material.reset();
		material = std::shared_ptr<AMaterial>(AMaterial::createFromSerialization(ret.at(2)));
		p.load(ret.at(3));
	}

	renderable* Pipe::clone() const {
		return new Pipe(p, radius, height, material);
	}

	size_t Pipe::size() const noexcept {
		return sizeof(Pipe);
	}
}