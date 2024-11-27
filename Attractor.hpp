#ifndef ATTRACTOR_HPP
#define ATTRACTOR_HPP

#include <list>
#include <string>
#include <SFML/Graphics.hpp>

typedef sf::Vector2<float> LVec2;
typedef sf::Vector3<float> LVec3;

struct AttractorParams {
    float dt = 0.01, sigma = 10, rho = 28, beta = 8/3;
    LVec3 start, origin;

    AttractorParams() : start(10, 10, 10), origin(0, 0, 0) {}

    void load(std::string);
    static AttractorParams fromfile(std::string);
};

class Attractor {
    const AttractorParams par;
    LVec3 pos;

public:
    Attractor() : pos(par.start) {}
    Attractor(AttractorParams p) : par(p), pos(par.start) {}
    Attractor(std::string f) : par(AttractorParams::fromfile(f)), pos(par.start) {}

    LVec3 iterate();
};

#endif
