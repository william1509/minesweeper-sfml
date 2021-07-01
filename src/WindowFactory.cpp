#include "WindowFactory.hpp"
#include "constants.h"

sf::RenderWindow* WindowFactory::MakeWindow() {
    float windowWidth = MINE_WIDTH * MINE_SIZE + MINE_MARGIN * (MINE_WIDTH + 1);

    float windowHeight = MINE_HEIGHT * MINE_SIZE + MINE_MARGIN * (MINE_HEIGHT + 1);
    static sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Scuffed minesweeper");

    return &window;
}