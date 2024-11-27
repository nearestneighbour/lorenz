#include <iostream>
#include <SFML/Graphics.hpp>
#include "Attractor.hpp"
#include "Trace.hpp"

TraceParams::TraceParams() {
    // default view - to do: check if it doesn't overwrite given parameters
    setscope(LVec3(-20, -22, -1), LVec3(23, 30, 51));
}

void TraceParams::load(std::string fname) {

}

TraceParams TraceParams::fromfile(std::string fname) {
    return TraceParams();
}

void TraceParams::setscope(LVec3 tl, LVec3 br) {
    topleft = tl;
    bottomright = br;
    size = (br.x-tl.x) > (br.y-tl.y) ? (br.x-tl.x) : (br.y-tl.y);
    size = size > (br.z-tl.z) ? size : (br.z-tl.z);
    // set offset
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
    LVec3 v = (p - topleft) / size;
    return choosedims(LVec2(v.x, v.y), LVec2(v.x, v.z), LVec2(v.y, v.z));
}

void Trace::step() {
    LVec3 p = att.iterate();
    LVec2 dot = par.normalize(p);
    dots.push_back(dot);
    if (dots.size() > N)
        dots.pop_front();
}

void Trace::draw(sf::RenderWindow& w) {
    LVec2 ws = (LVec2)w.getSize();
    float scale = (ws.x < ws.y) ? ws.x : ws.y;
    sf::VertexArray line(sf::LineStrip, dots.size());
    int i = 0;
    for (sf::Vector2f d : dots) {
        line[i].position = scale * d;
        //std::cout << line[i].position.x << " " << line[i].position.y << std::endl;
        //std::cout << d.x << " " << d.y << std::endl;
        i++;
    }
    w.draw(line);
}
