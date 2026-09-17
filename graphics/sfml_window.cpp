//
// Created by Omeed on 8/30/26.
//

#include "sfml_window.h"

sfml_handler::sfml_handler(thread_data* data) {
    w = sf::RenderWindow(sf::VideoMode({800, 600}), "SFML");
    t_data = data;
}

void sfml_handler::init_window() {
    while (w.isOpen()) {
        while (const std::optional<sf::Event> event = w.pollEvent()) {

        }
    }
}