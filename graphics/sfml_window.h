//
// Created by Omeed on 8/30/26.
//

#ifndef SFML_WINDOW_H
#define SFML_WINDOW_H

#include "SFML/Graphics.hpp"

class thread_data;

class sfml_handler {
private:
    thread_data* t_data;
    sf::RenderWindow w;
public:
    sfml_handler(thread_data* data);
    void init_window();
};

#endif //SFML_WINDOW_H
