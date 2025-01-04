#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Params.hpp"
#include "Attractor.hpp"

LVec3 Lorenz::iterate() {
    //std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
    LVec3 dp, p(pos-par.origin);
    dp.x = par.sigma * (p.y-p.x);
    dp.y = p.x * (par.rho-p.z) - p.y;
    dp.z = p.x * p.y - par.beta * p.z;
    pos += dp * par.dt;
    return pos;
}

void Lorenz::rotate(LVec3 ax, float a) {
    ax /= (float)sqrt(pow(ax.x, 2)+pow(ax.y, 2)+pow(ax.z, 2));
    float dotp;
    LVec3 crossp;
    for (LVec3& d : dots) {
        d -= par.origin;
        dotp = d.x * ax.x + d.y * ax.y + d.z * ax.z;
        crossp.x = ax.y * d.z - ax.z - d.y;
        crossp.y = ax.z * d.x - ax.x * d.z;
        crossp.z = ax.x * d.y - ax.y * d.x;
        d = par.origin + d * cos(a) + crossp * sin(a) + ax * dotp * (1 - cos(a));
    }
}

void Lorenz::step() {
    dots.push_back(iterate());
    if (dots.size() > par.maxn)
        dots.pop_front();
    if (par.rot > 0)
        rotate(LVec3(0,0,1), par.rot);
}

void Lorenz::draw(sf::RenderWindow& w) {
    LVec2 ws = (LVec2)w.getSize();
    float scale = (ws.x < ws.y) ? ws.x : ws.y;
    sf::VertexArray line(sf::LineStrip, dots.size());
    int i = 0;
    for (LVec3 d : dots) {
        line[i].position = scale * par.normalize(d);
        //std::cout << line[i].position.x << " " << line[i].position.y << std::endl;
        //std::cout << d.x << " " << d.y << std::endl;
        i++;
    }
    w.draw(line);
}
