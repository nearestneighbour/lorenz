#include <iostream>
#include <fstream>
#include <math.h>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Params.hpp"

Params::Params() : start(10, 10, 10), origin(0, 0, 0) {
    setscope(LVec3(-20, -22, -1), LVec3(23, 30, 51));
}

Params::Params(std::string fname) : Params() {
    load(fname);
}

void Params::setscope(LVec3 tl, LVec3 br) {
    topleft = tl;
    bottomright = br;
    size = (br.x-tl.x) > (br.y-tl.y) ? (br.x-tl.x) : (br.y-tl.y);
    size = size > (br.z-tl.z) ? size : (br.z-tl.z);
    offset = (LVec3(size, size, size) - (br-tl)) / 2.0f;
}

void Params::load(std::string fname) {
    void (*error)(const std::string&, bool) = [](const std::string& e, bool q){
        std::cerr << e << std::endl;
        if (q) exit(0);
    };

    const std::unordered_map<std::string, void(*)(const std::string&, Params*)> ConfMap {
        { "ROT",   [](const std::string& s, Params* t) { t->rot      = std::stod(s); } },
        { "DT",    [](const std::string& s, Params* t) { t->dt       = std::stod(s); } },
        { "SIGMA", [](const std::string& s, Params* t) { t->sigma    = std::stod(s); } },
        { "RHO",   [](const std::string& s, Params* t) { t->rho      = std::stod(s); } },
        { "BETA",  [](const std::string& s, Params* t) { t->beta     = std::stod(s); } },
        { "STARTX",[](const std::string& s, Params* t) { t->start.x  = std::stod(s); } },
        { "STARTY",[](const std::string& s, Params* t) { t->start.y  = std::stod(s); } },
        { "STARTZ",[](const std::string& s, Params* t) { t->start.z  = std::stod(s); } },
        { "ORIGX", [](const std::string& s, Params* t) { t->origin.x = std::stod(s); } },
        { "ORIGY", [](const std::string& s, Params* t) { t->origin.y = std::stod(s); } },
        { "ORIGZ", [](const std::string& s, Params* t) { t->origin.z = std::stod(s); } },
        /*{ "DIMS", [](const std::string& s, Params* t) { t->dims = ??; } },
        { "WINW",  [](const std::string& s) { winw  = std::stoi(s); } },
        { "WINH",  [](const std::string& s) { winh  = std::stoi(s); } },
        */
    };

    std::ifstream f(fname);
    if (!f.is_open()) {
        error("Could not load config file " + fname, true);
        return;
    }

    std::string ln, key, val;
    while (std::getline(f, ln)) {
        if (ln.empty() || ln[0] == '#') continue;
        ln.erase(std::remove(ln.begin(), ln.end(), ' '), ln.end());

        std::size_t ix = ln.find('=');
        if (ix == std::string::npos) break;

        key = ln.substr(0, ix);
        val = ln.substr(ix + 1);

        if (auto i = ConfMap.find(key); i != ConfMap.end()) i->second(val, this);
        else error("Unknown setting: " + key, true);
    }
}

float Params::aspectratio() const {
    LVec3 diff = bottomright - topleft;
    return choosedims(diff.x/diff.y, diff.x/diff.z, diff.y/diff.z);
}

template <typename T>
T Params::choosedims(T a, T b, T c) const {
    switch (dims) {
        case Dims::XY: return a;
        case Dims::XZ: return b;
        case Dims::YZ: return c;
        default: return a;
    }
}

LVec2 Params::normalize(LVec3 p) const {
    LVec3 v = (p - topleft + offset) / size;
    return choosedims(LVec2(v.x, v.y), LVec2(v.x, v.z), LVec2(v.y, v.z));
}
