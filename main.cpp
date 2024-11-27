#include <SFML/Graphics.hpp>
#include "Attractor.hpp"
#include "Trace.hpp"

void handle_events(sf::Event&);
sf::RenderWindow W;

int main() {

    W.create(sf::VideoMode(800, 800), "ddd");
    W.setFramerateLimit(30);

    AttractorParams par2;
    par2.start = LVec3(10, 10, 10.0001);
    Trace lor1, lor2(par2);

    while (W.isOpen()) {
        sf::Event ev;
        while (W.pollEvent(ev))
            handle_events(ev);

        W.clear(sf::Color::Black);
        lor1.step();
        lor1.draw(W);
        lor2.step();
        lor2.draw(W);
        W.display();
    }

    return 0;
}

void handle_events(sf::Event& ev) {
    if (ev.type == sf::Event::Closed) {
        W.close(); exit(0);
    } else if (ev.type == sf::Event::MouseButtonPressed) {
        if (ev.mouseButton.button == sf::Mouse::Right) {
            W.close(); exit(0);
        }
    }
}
