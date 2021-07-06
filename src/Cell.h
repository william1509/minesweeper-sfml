#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <string>
#include "constants.h"

class Cell {
    public:
        Cell(sf::Vector2f cellPosition, bool isMine, int cellID);
        Cell();
        bool Contains(sf::Vector2f mousePosition);
        void SetNumberMines(int numberMines);
        void LClicked();
        void RClicked();

        sf::RectangleShape rectangle;
        sf::Text minesLabel;
        int numberMines;
        bool _isMine;
        bool _isClicked;
        int cellID;
        int rowNumber;
        bool _isFlagged;

};

#endif