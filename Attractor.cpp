#include <iostream>
#include <SFML/Graphics.hpp>
#include "Attractor.hpp"

void AttractorParams::load(std::string fname) {

}

AttractorParams AttractorParams::fromfile(std::string fname) {
    return AttractorParams();
}

LVec3 Attractor::iterate() {
    //std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
    LVec3 dp, p(pos-par.origin);
    dp.x = par.sigma * (p.y-p.x);
    dp.y = p.x * (par.rho-p.z) - p.y;
    dp.z = p.x * p.y - par.beta * p.z;
    pos += dp * par.dt;
    return pos;
}
