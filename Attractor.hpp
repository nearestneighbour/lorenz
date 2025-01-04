#ifndef ATTRACTOR_HPP
#define ATTRACTOR_HPP

#include <list>
#include <string>
#include <SFML/Graphics.hpp>

typedef sf::Vector2<float> LVec2;
typedef sf::Vector3<float> LVec3;

class Lorenz {
    const Params par;
    std::list<LVec3> dots;
    LVec3 pos;

    LVec3 iterate();
    void rotate(LVec3, float);

public:
    Lorenz() : pos(par.start) {}
    Lorenz(Params p) : par(p), pos(par.start) {}
    Lorenz(std::string f) : par(f), pos(par.start) {}

    void step();
    void draw(sf::RenderWindow&);
};

#endif
