#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <list>
#include <string>
#include <SFML/Graphics.hpp>

typedef sf::Vector2<float> LVec2;
typedef sf::Vector3<float> LVec3;

struct Params {
    enum class Dims {XY, XZ, YZ} dims{Dims::YZ};
    float dt = 0.01, sigma = 10, rho = 28, beta = 8/3, rot = 0;
    unsigned long maxn = 400;
    LVec3 start, origin;
    sf::Color color = sf::Color::White;

    Params();
    Params(std::string);

    void load(std::string);
    void setscope(LVec3, LVec3);
    float aspectratio() const;
    template <typename T> T choosedims(T, T, T) const;
    LVec2 normalize(LVec3) const;

private:
    LVec3 topleft, bottomright, offset;
    float size;
};

#endif
