#include "Cell.h"
#include "Logger.h"
#include <math.h>

Cell::Cell(sf::Vector2f cellPosition, bool isMine, int cellID) {

    sf::RectangleShape rect(sf::Vector2f(MINE_SIZE, MINE_SIZE));
    rect.setPosition(cellPosition);
    //rect.setFillColor(sf::Color(200, 200, 200));

    

    static sf::Font font;
    font.loadFromFile("../fonts/aovel.ttf");
    
    sf::Text text("", font, 16);

    sf::FloatRect rectBounds = rect.getGlobalBounds();
    sf::FloatRect textBounds = text.getGlobalBounds();

    text.setPosition(
    rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
    rectBounds.top + (rectBounds.height / 2) - textBounds.height
    );

    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Blue);

    this->minesLabel = text;

    this->_isMine = isMine;

    this->_isClicked = false;
    this->cellID = cellID;
    this->rowNumber = cellID / MINE_WIDTH;
    this->rectangle = rect;

}

void Cell::Clicked() {
    this->_isClicked = true;
    if(this->_isMine) {
        this->rectangle.setFillColor(sf::Color().Red);
    } else {
        this->rectangle.setFillColor(sf::Color(150, 150, 150));
    }
} 

void Cell::SetNumberMines(int numberMines) {
    this->numberMines = numberMines;
    this->minesLabel.setString(std::to_string(numberMines));
}

bool Cell::Contains(sf::Vector2f mousePosition) {
    sf::RectangleShape mouseRectangle(sf::Vector2f(1, 1));
    mouseRectangle.setPosition(mousePosition);
    return this->rectangle.getGlobalBounds().intersects(mouseRectangle.getGlobalBounds());
}