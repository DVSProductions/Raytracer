#include "Dice.h"
namespace DDD {
	Dice::Dice(std::string serialized) {
	}
	renderable* Dice::evaluate(uint64_t startSeed) const{
		return children.at(std::round(randfast(startSeed)(0, children.size() - 1)))->evaluate(startSeed + 1);
	}
	std::string Dice::serialize() const {
		return "";
	}
	void Dice::load(std::string serialized) {
	}
	size_t Dice::size() const noexcept {
		return sizeof(Dice);
	}
}