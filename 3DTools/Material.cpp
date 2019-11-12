#include "Material.h"
#include <stdexcept>
#define deserial(Material) case Material::CLASSID: return new Material(s.at(1))
#define MaterialSplitter "}"
namespace DDD {
	AMaterial::AMaterial() {
		std::random_device rd;
		mt = std::mt19937(rd());
	}
	AMaterial::AMaterial(cgtools::Color emi, cgtools::Color alb) {
		emission = emi;
		albedo = alb;
	}
	std::string DDD::AMaterial::includeClassID(std::string data, int CID) {
		return std::string();
	}

	DDD::AMaterial* DDD::AMaterial::createFromSerialization(std::string data) {
		const auto s = Serializable::split(data, "#");
		if (s.size() == 0 || s.size() == 1)
			return new Vanta(data);
		int n = -1;
		f_chars(s.at(0), n);
		switch (n) {
			deserial(Vanta);
			deserial(Mirror);
			deserial(Chalk);
		}
		return nullptr;
	}

	void AMaterial::operator=(const AMaterial& para) {
		scatterFactor = para.scatterFactor;
		emission = para.emission;
		albedo = para.albedo;
	}


	Vanta::Vanta(std::string serialized) {
		load(serialized);
	}

	Vanta::Vanta(cgtools::Color Material) {
		scatterFactor = 0;
		emission = Material;
		albedo = cgtools::c_black;
	}
	Ray Vanta::scatteredRay(Hit origin, Ray originalRay) {
		throw std::logic_error("Vanta Fully absorbes Rays!");
	}
	std::string Vanta::serialize() const {
		return AMaterial::includeClassID(emission.serialize(), CLASSID);
	}
	void Vanta::load(std::string serialized) {
		/// <summary>
		/// ensure compatablility with colors
		/// </summary>
		/// <param name="serialized"></param>
		scatterFactor = 0;
		emission.load(serialized);
		albedo = cgtools::c_black;
		return;
	}
	AMaterial* Vanta::clone() const {
		return new Vanta(emission);
	}
	size_t Vanta::size() const {
		return sizeof(Vanta);
	}


	Mirror::Mirror(std::string serialized) {
		scatterFactor = 0;
		load(serialized);
	}
	Mirror::Mirror(cgtools::Color Material) {
		scatterFactor = 0;
		emission = Material;
		albedo = cgtools::c_white;
	}
	Mirror::Mirror(cgtools::Color Emi, cgtools::Color Albe) {
		scatterFactor = 0;
		emission = Emi;
		albedo = Albe;
	}
	Ray Mirror::scatteredRay(Hit origin, Ray originalRay) {
		return Ray(origin.pos, originalRay.dir * -1, originalRay.tmax, 0);
	}
	std::string Mirror::serialize() const {
		return AMaterial::includeClassID(albedo.serialize() + MaterialSplitter + emission.serialize() + MaterialSplitter, CLASSID);
	}
	void Mirror::load(std::string serialized) {
		auto ret = Serializable::split(serialized, MaterialSplitter);
		albedo.load(ret.at(0));
		emission.load(ret.at(1));
	}
	AMaterial* Mirror::clone() const {
		return new Mirror(emission, albedo);
	}
	size_t Mirror::size() const {
		return sizeof(Mirror);
	}


	Chalk::Chalk(std::string serialized) {
		scatterFactor = 1;
		load(serialized);
	}
	Chalk::Chalk(cgtools::Color Emi, cgtools::Color alb) {
		scatterFactor = 1;
		dist = std::normal_distribution<double>(0, scatterFactor);
		albedo = alb;
		emission = Emi;
	}
	Ray Chalk::scatteredRay(Hit origin, Ray originalRay) {
		return Ray(origin.pos, ~cgtools::direction(dist(mt), dist(mt), dist(mt)) + origin.n, originalRay.tmax, 0.000001);
	}
	std::string Chalk::serialize() const {
		return AMaterial::includeClassID(albedo.serialize() + MaterialSplitter + emission.serialize() + MaterialSplitter, CLASSID);
	}
	void Chalk::load(std::string serialized) {
		auto ret = Serializable::split(serialized, MaterialSplitter);
		albedo.load(ret.at(0));
		emission.load(ret.at(1));
	}
	AMaterial* Chalk::clone() const {
		return new Chalk(emission, albedo);
	}
	size_t Chalk::size() const {
		return sizeof(Chalk);
	}
}