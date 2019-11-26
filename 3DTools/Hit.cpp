#include "Hit.h"
#include "Vanta.h"
#include <math.h>
DDD::Hit::Hit()noexcept : pos(0, 0, 0), n(0, 0, 0), material(nullptr), t(0) {
	this->hit = false;
}
DDD::Hit::Hit(double t, cgtools::point pos, cgtools::direction n, std::shared_ptr<AMaterial>  m)noexcept :pos(pos), n(n), material(m) {
	this->t = t;
	this->hit = true;
}

DDD::Hit::Hit(double t, cgtools::point pos, cgtools::direction n, cgtools::Color Material) : Hit(t, pos, n, std::make_unique<Vanta>(Vanta(Material))) {

}

cgtools::Color DDD::Hit::shade() const noexcept {
	return material->emission * 0.1 + material->emission * (0.9 * fmax(0, (~cgtools::direction(1, 1, 0.5))[n]));
}
