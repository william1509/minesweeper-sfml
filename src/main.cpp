#include <SFML/Graphics.hpp>
#include "BigRectangleShape.h"
#include "Renderer.h"
#include "constants.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Scuffed minesweeper");
    
    Renderer* r = new Renderer(&window);
    r->StartGameLoop();

    return 0;
}