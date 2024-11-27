#ifndef TRACE_HPP
#define TRACE_HPP

#include <list>
#include <string>
#include <SFML/Graphics.hpp>

typedef sf::Vector2<float> LVec2;
typedef sf::Vector3<float> LVec3;

struct TraceParams {
    enum class Dims {XY, XZ, YZ} dims{Dims::YZ};

    TraceParams();

    void load(std::string);
    static TraceParams fromfile(std::string);
    void setscope(LVec3, LVec3);
    float aspectratio() const;
    template <typename T> T choosedims(T, T, T) const;
    LVec2 normalize(LVec3) const;

private:
    LVec3 topleft, bottomright;
    float size, offset;
};

class Trace {
    const TraceParams par;
    Attractor att;
    std::list<LVec2> dots;
    const unsigned int N = 100;

public:
    Trace() {}
    Trace(Attractor a) : att(a) {}
    Trace(AttractorParams p) : att(p) {}
    Trace(std::string f) :att(f) {}
    void step();
    void draw(sf::RenderWindow&);
};

#endif
