#include <vector>
#include <SFML/Graphics.hpp>
#include "Params.hpp"
#include "Attractor.hpp"

void handle_events(sf::Event&);
sf::RenderWindow W;

int main(int argc, char* argv[]) {

    W.create(sf::VideoMode(800, 800), "ddd");
    W.setFramerateLimit(30);

    std::vector<Lorenz> L;
    if (argc > 1) {
        for (int i=1; i<argc; i++) {
            L.push_back(Lorenz(argv[i]));
        }
    } else {
        L.push_back(Lorenz());
    }

    while (W.isOpen()) {
        sf::Event ev;
        while (W.pollEvent(ev))
            handle_events(ev);

        W.clear(sf::Color::Black);
        for (Lorenz& l : L) {
            l.step();
            l.draw(W);
        }
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
