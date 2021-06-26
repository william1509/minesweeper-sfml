#include "Renderer.h"
#include <iostream>
#include <time.h>

Renderer::Renderer(sf::RenderWindow *window) {
    this->window = window;
    CreateCells();
    SetCellMines();
};

void Renderer::StartGameLoop() {
    window->setFramerateLimit(30);
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {   
            if (event.type == sf::Event::MouseButtonPressed) {

                sf::Vector2f position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window));

                for(auto cell : this->cells) {
                    if(cell->Contains(position)){
                        cell->Clicked();
                        if(cell->numberMines == 0) {
                            RevealEmptyCells(cell);
                        }
                    }
                }

            }
            
            if (event.type == sf::Event::Closed)
                window->close();
        }


        window->clear();
        DrawGrid();

        window->display();
    }
}

void Renderer::DrawGrid() {
    std::for_each(this->cells.begin(), this->cells.end(), [this](Cell* cell) {
        
        this->window->draw(cell->rectangle);
        if(cell->_isClicked) {
            if(!cell->_isMine) {
                this->window->draw(cell->minesLabel);
                cell->rectangle.setFillColor(sf::Color(150, 150, 150));
            }
        }
        
    });
}

void Renderer::SetCellMines() {
    for(int i = 0; i < this->cells.size(); i++) {
        int totalMines = 0;

        int rowNumber = this->cells[i]->rowNumber;

        // Left
        if(i > 0 && this->cells[i - 1]->rowNumber == rowNumber) {
            totalMines += (int)this->cells[i - 1]->_isMine;
        }
        
        // Right
        if(i < (pow(N_TILES, 2) - 1) && this->cells[i + 1]->rowNumber == rowNumber) {
            totalMines += (int)this->cells[i + 1]->_isMine;
        }

        // Top
        if((i - N_TILES) > 0) totalMines += (int)this->cells[i - N_TILES]->_isMine;

        // Bottom
        if((i + N_TILES) < pow(N_TILES, 2)) totalMines += (int)this->cells[i + N_TILES]->_isMine;

        // Top left
        if((i - N_TILES - 1) > 0) totalMines += (int)this->cells[i - N_TILES - 1]->_isMine;

        // Bottom right
        if((i + N_TILES + 1) < pow(N_TILES, 2)) totalMines += (int)this->cells[i + N_TILES + 1]->_isMine;

        // Top right
        if((i - N_TILES + 1) > 0) totalMines += (int)this->cells[i - N_TILES + 1]->_isMine;

        // Bottom left
        if((i + N_TILES - 1) < pow(N_TILES, 2)) totalMines += (int)this->cells[i + N_TILES - 1]->_isMine;
        
        this->cells[i]->SetNumberMines(totalMines);
    }
}

double Renderer::CalculateOffset() {
    double offset = (double)(window->getSize().x - N_TILES * TILE_WIDTH);

    if(offset <= 0) {
        return -1.0;
    };
    
    offset /= (N_TILES + 1.0);
    return offset;
}

void Renderer::RevealEmptyCells(Cell* startingCell) {
    Cell* currentCell = startingCell;
    std::vector<Cell*> cellsToCheck;

    cellsToCheck.push_back(startingCell);

    while(!cellsToCheck.empty()) {

        currentCell = cellsToCheck.back();
        cellsToCheck.pop_back();
 
        int cellID = currentCell->cellID;
        currentCell->Clicked();

        int rowNumber = currentCell->rowNumber;

        // Left
        if(cellID - 1 >= 0 && this->cells[cellID - 1]->numberMines == 0 && !this->cells[cellID - 1]->_isClicked && this->cells[cellID - 1]->rowNumber == rowNumber) {
            cellsToCheck.push_back(this->cells[cellID - 1]);
        }
        
        // Right
        if(cellID + 1 < (pow(N_TILES, 2) - 1) && this->cells[cellID + 1]->numberMines == 0 && !this->cells[cellID + 1]->_isClicked && this->cells[cellID + 1]->rowNumber == rowNumber) {
            cellsToCheck.push_back(this->cells[cellID + 1]);
        }

        // Top
        if((cellID - N_TILES) > 0 && this->cells[cellID - N_TILES]->numberMines == 0 && !this->cells[cellID - N_TILES]->_isClicked) {
            cellsToCheck.push_back(this->cells[cellID - N_TILES]);
        } 

        // Bottom
        if((cellID + N_TILES) < (pow(N_TILES, 2) - 1) && this->cells[cellID + N_TILES]->numberMines == 0 && !this->cells[cellID + N_TILES]->_isClicked) {
            cellsToCheck.push_back(this->cells[cellID + N_TILES]);
        } 
    }
}

void Renderer::CreateCells() {
    double offset = CalculateOffset();
    if(offset < 0) {
        Logger::Log("Error creating cells");
        return;
    }
    int totalNumberTiles = pow(N_TILES, 2);
    std::vector<int> randomNumbers = GenerateRandomInRange(0, totalNumberTiles, totalNumberTiles / 9);

    int cellID = 0;
    sf::Vector2f tilePosition = sf::Vector2f(offset, offset);
    for (size_t i = 0; i < N_TILES; i++) {
        for (size_t j = 0; j < N_TILES; j++) {

            Cell* cell = new Cell(tilePosition, false, cellID);

            if(std::find(randomNumbers.begin(), randomNumbers.end(), cellID) != randomNumbers.end()) {
                cell->_isMine = true;
            }
            this->cells.push_back(cell);

            tilePosition += sf::Vector2f(0, TILE_WIDTH + offset);

            cellID++;
        }
        tilePosition = sf::Vector2f(tilePosition.x + TILE_WIDTH + offset, offset);
    }
}

std::vector<int> Renderer::GenerateRandomInRange(int lBound, int uBound, int nNumbers) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(lBound, uBound);

    std::vector<int> randomNumbers;

    for(int i = 0; i < nNumbers; i++) {
        randomNumbers.push_back(distr(gen));
    }

    return randomNumbers;
}





