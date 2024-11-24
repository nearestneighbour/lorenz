#include <SFML/Graphics.hpp>
#include "Lorenz.hpp"

void handle_events(sf::Event&);
sf::RenderWindow W;

int main() {

    W.create(sf::VideoMode(800, 800), "ddd");
    W.setFramerateLimit(30);

    Params p;
    p.start = LVec3(1, 1, 1.0001);
    Lorenz lor, lor1(p);

    while (W.isOpen()) {
        sf::Event ev;
        while (W.pollEvent(ev))
            handle_events(ev);

        W.clear(sf::Color::Black);
        lor.iterate();
        lor.draw(W);
        lor1.iterate();
        lor1.draw(W);
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
