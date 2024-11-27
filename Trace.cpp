#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Attractor.hpp"
#include "Trace.hpp"

TraceParams::TraceParams() {
    setscope(LVec3(-20, -22, -1), LVec3(23, 30, 51), LVec3(0, 0, 0));
}

void TraceParams::load(std::string fname) {

}

TraceParams TraceParams::fromfile(std::string fname) {
    return TraceParams();
}

void TraceParams::setscope(LVec3 tl, LVec3 br, LVec3 ct) {
    topleft = tl;
    bottomright = br;
    center = ct;
    size = (br.x-tl.x) > (br.y-tl.y) ? (br.x-tl.x) : (br.y-tl.y);
    size = size > (br.z-tl.z) ? size : (br.z-tl.z);
    offset = (LVec3(size, size, size) - (br-tl)) / 2.0f;
}

float TraceParams::aspectratio() const {
    LVec3 diff = bottomright - topleft;
    return choosedims(diff.x/diff.y, diff.x/diff.z, diff.y/diff.z);
}

template <typename T>
T TraceParams::choosedims(T a, T b, T c) const {
    switch (dims) {
        case Dims::XY: return a;
        case Dims::XZ: return b;
        case Dims::YZ: return c;
        default: return a;
    }
}

LVec2 TraceParams::normalize(LVec3 p) const {
    LVec3 v = (p - topleft + offset) / size;
    return choosedims(LVec2(v.x, v.y), LVec2(v.x, v.z), LVec2(v.y, v.z));
}

void Trace::rotate(LVec3 ax, float a) {
    ax /= (float)sqrt(pow(ax.x, 2)+pow(ax.y, 2)+pow(ax.z, 2));
    float dotp;
    LVec3 crossp;
    for (LVec3& d : dots) {
        d -= par.center;
        dotp = d.x * ax.x + d.y * ax.y + d.z * ax.z;
        crossp.x = ax.y * d.z - ax.z - d.y;
        crossp.y = ax.z * d.x - ax.x * d.z;
        crossp.z = ax.x * d.y - ax.y * d.x;
        d = par.center + d * cos(a) + crossp * sin(a) + ax * dotp * (1 - cos(a));
    }
}

void Trace::step() {
    dots.push_back(att.iterate());
    if (dots.size() > N)
        dots.pop_front();
    rotate(LVec3(0,0,1), par.rotspeed);
}

void Trace::draw(sf::RenderWindow& w) {
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
