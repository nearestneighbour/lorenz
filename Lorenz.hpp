#ifndef LORENZ_HPP
#define LORENZ_HPP

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

typedef sf::Vector3<float> LVec3;

struct Params {
    float dt = 0.01, sigma = 10, rho = 28, beta = 8/3;
    std::list<sf::Vector2f>::size_type N = 100;
    LVec3 start;
    sf::Vector2f min, max;
    Params() : start(1, 1, 1), min(0, 0), max(2, 2) {}
};

struct Lorenz {
    const Params par;
    LVec3 pos;
    std::list<sf::Vector2f> dots;
    sf::Vector2f min, max;

    Lorenz();
    Lorenz(Params);

    void iterate();
    void draw(sf::RenderWindow&);
};

#endif
