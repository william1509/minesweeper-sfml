#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "constants.h"
#include "WindowFactory.hpp"

int main()
{
    WindowFactory wf;

    sf::RenderWindow* window = wf.MakeWindow();
    
    Renderer* r = new Renderer(window);
    r->StartGameLoop();

    return 0;
}