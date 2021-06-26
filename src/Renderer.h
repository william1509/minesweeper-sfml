#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

#include "Cell.h"
#include "Logger.h"
#include "constants.h"

class Renderer {
    private:
        sf::RenderWindow *window;
        void DrawGrid();
        double CalculateOffset();
        void SetCellMines();
        void RevealEmptyCells(Cell* startingCell);

        std::vector<Cell*> cells;
        void CreateCells();

        std::vector<int> GenerateRandomInRange(int lBound, int uBound, int nNumbers);
        
    protected:
        
    public:
        Renderer(sf::RenderWindow *window);
        void StartGameLoop();
        

};
#endif