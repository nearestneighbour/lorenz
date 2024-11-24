#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lorenz.hpp"

Lorenz::Lorenz() : pos(par.start) {}
Lorenz::Lorenz(Params p) : par(p), pos(par.start) {}

template <class T>
T min(T x, T y) { return x < y ? x : y; }
template <class T>
T max(T x, T y) { return x > y ? x : y; }

void Lorenz::iterate() {
    LVec3 dp;
    dp.x = par.sigma * (pos.y-pos.x);
    dp.y = pos.x * (par.rho-pos.z) - pos.y;
    dp.z = pos.x * pos.y - par.beta * pos.z;
    pos += dp * par.dt;
    dots.push_back(sf::Vector2f(pos.x, pos.z));
    if (dots.size() > par.N)
        dots.pop_front();

    min.x = pos.x < min.x ? pos.x : min.x;
    min.y = pos.z < min.y ? pos.z : min.y;
    max.x = pos.x > max.x ? pos.x : max.x;
    max.y = pos.z > max.y ? pos.z : max.y;
}

void Lorenz::draw(sf::RenderWindow& w) {
    sf::Vector2f ws = (sf::Vector2f)w.getSize(), diff(max-min);
    float sz = diff.x > diff.y ? diff.x : diff.y;
    sf::Vector2f offset((sz-diff.x)/2, (sz-diff.y)/2);
    sf::VertexArray line(sf::LineStrip, dots.size());
    int i = 0;
    for (sf::Vector2f d : dots) {
        line[i].position = sf::Vector2f(ws.x * (d.x+offset.x-min.x) / sz,
                                        ws.y * (d.y+offset.y-min.y) / sz);
        i++;
    }
    w.draw(line);
}
