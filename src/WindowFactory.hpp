#ifndef WINDOW_FACTORY_H
#define WINDOW_FACTORY_H

#include <SFML/Graphics.hpp>


class WindowFactory {
    public:
        WindowFactory() = default;
        sf::RenderWindow* MakeWindow();
};

#endif