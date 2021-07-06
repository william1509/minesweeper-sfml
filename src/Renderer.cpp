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

                        if(event.mouseButton.button == sf::Mouse::Left) {
                            cell->LClicked();

                            if(cell->numberMines == 0 && !cell->_isMine) {
                                RevealEmptyCells(cell);
                            }
                        } else if(event.mouseButton.button == sf::Mouse::Right) {
                            cell->RClicked();
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
        if(i < (MINE_WIDTH * MINE_HEIGHT - 1) && this->cells[i + 1]->rowNumber == rowNumber) {
            totalMines += (int)this->cells[i + 1]->_isMine;
        }

        // Top
        if((i - MINE_WIDTH) > 0) totalMines += (int)this->cells[i - MINE_WIDTH]->_isMine;

        // Bottom
        if((i + MINE_WIDTH) < (MINE_WIDTH * MINE_HEIGHT)) totalMines += (int)this->cells[i + MINE_WIDTH]->_isMine;

        // Top left
        if((i - MINE_WIDTH - 1) > 0) totalMines += (int)this->cells[i - MINE_WIDTH - 1]->_isMine;

        // Bottom right
        if((i + MINE_WIDTH + 1) < (MINE_WIDTH * MINE_HEIGHT)) totalMines += (int)this->cells[i + MINE_WIDTH + 1]->_isMine;

        // Top right
        if((i - MINE_WIDTH + 1) > 0) totalMines += (int)this->cells[i - MINE_WIDTH + 1]->_isMine;

        // Bottom left
        if((i + MINE_WIDTH - 1) < (MINE_WIDTH * MINE_HEIGHT)) totalMines += (int)this->cells[i + MINE_WIDTH - 1]->_isMine;
        
        this->cells[i]->SetNumberMines(totalMines);
    }
}
void Renderer::RevealEmptyCells(Cell* startingCell) {
    
    std::vector<Cell*> cellsToCheck;
    Cell* currentCell;
    cellsToCheck.push_back(startingCell);

    while(!cellsToCheck.empty()) {

        currentCell = cellsToCheck.back();
        cellsToCheck.pop_back();
 
        currentCell->LClicked();

        int rowNumber = currentCell->rowNumber;

        int cellID = currentCell->cellID - 1;
        // left
        if(cellID >= 0 && cellID < (MINE_WIDTH * MINE_HEIGHT) && !this->cells[cellID]->_isClicked && this->cells[cellID]->rowNumber == rowNumber) {
            if(this->cells[cellID]->numberMines == 0) {
                    cellsToCheck.push_back(this->cells[cellID]);
                } else {
                    this->cells[cellID]->LClicked();
            }
        }

        cellID = currentCell->cellID + 1;
        // right
        if(cellID >= 0 && cellID < (MINE_WIDTH * MINE_HEIGHT) && !this->cells[cellID]->_isClicked && this->cells[cellID]->rowNumber == rowNumber) {
            if(this->cells[cellID]->numberMines == 0) {
                    cellsToCheck.push_back(this->cells[cellID]);
                } else {
                    this->cells[cellID]->LClicked();
            }
        }

        cellID = currentCell->cellID - MINE_WIDTH;
        // top
        if(cellID >= 0 && cellID < (MINE_WIDTH * MINE_HEIGHT) && !this->cells[cellID]->_isClicked) {
            if(this->cells[cellID]->numberMines == 0) {
                    cellsToCheck.push_back(this->cells[cellID]);
                } else {
                    this->cells[cellID]->LClicked();
            }
        }

        cellID = currentCell->cellID + MINE_WIDTH;
        // bottom
        if(cellID >= 0 && cellID < (MINE_WIDTH * MINE_HEIGHT) && !this->cells[cellID]->_isClicked) {
            if(this->cells[cellID]->numberMines == 0) {
                    cellsToCheck.push_back(this->cells[cellID]);
                } else {
                    this->cells[cellID]->LClicked();
            }
        }

        cellID = currentCell->cellID - MINE_WIDTH - 1;
        // top left
        if(cellID >= 0 && cellID < (MINE_WIDTH * MINE_HEIGHT) && !this->cells[cellID]->_isClicked && this->cells[cellID]->rowNumber == this->cells[cellID + 1]->rowNumber) {
            if(this->cells[cellID]->numberMines == 0) {
                    cellsToCheck.push_back(this->cells[cellID]);
                } else {
                    this->cells[cellID]->LClicked();
            }
        }

        cellID = currentCell->cellID + MINE_WIDTH + 1;
        // top right
        if(cellID >= 0 && cellID < (MINE_WIDTH * MINE_HEIGHT) && !this->cells[cellID]->_isClicked && this->cells[cellID]->rowNumber == this->cells[cellID - 1]->rowNumber) {
            if(this->cells[cellID]->numberMines == 0) {
                    cellsToCheck.push_back(this->cells[cellID]);
                } else {
                    this->cells[cellID]->LClicked();
            }
        }

        cellID = currentCell->cellID - MINE_WIDTH + 1;
        // bottom left
        if(cellID >= 0 && cellID < (MINE_WIDTH * MINE_HEIGHT) && !this->cells[cellID]->_isClicked && this->cells[cellID]->rowNumber == this->cells[cellID - 1]->rowNumber) {
            if(this->cells[cellID]->numberMines == 0) {
                    cellsToCheck.push_back(this->cells[cellID]);
                } else {
                    this->cells[cellID]->LClicked();
            }
        }

        cellID = currentCell->cellID + MINE_WIDTH - 1;
        // bottom right
        if(cellID >= 0 && cellID < (MINE_WIDTH * MINE_HEIGHT) && !this->cells[cellID && this->cells[cellID]->rowNumber == this->cells[cellID + 1]->rowNumber]->_isClicked) {
            if(this->cells[cellID]->numberMines == 0) {
                    cellsToCheck.push_back(this->cells[cellID]);
                } else {
                    this->cells[cellID]->LClicked();
            }
        }
    }
}

void Renderer::CreateCells() {
    double offset = MINE_MARGIN;
    if(offset < 0) {
        Logger::Log("Error creating cells");
        return;
    }
    int totalNumberTiles = MINE_WIDTH * MINE_HEIGHT;
    std::vector<int> randomNumbers = GenerateRandomInRange(0, totalNumberTiles, totalNumberTiles * P_MINE);

    int cellID = 0;
    sf::Vector2f tilePosition = sf::Vector2f(offset, offset);
    for (size_t i = 0; i < MINE_HEIGHT; i++) {
        for (size_t j = 0; j < MINE_WIDTH; j++) {

            Cell* cell = new Cell(tilePosition, false, cellID);

            if(std::find(randomNumbers.begin(), randomNumbers.end(), cellID) != randomNumbers.end()) {
                cell->_isMine = true;
            }
            this->cells.push_back(cell);

            tilePosition += sf::Vector2f(MINE_SIZE + offset, 0);

            cellID++;
        }
        tilePosition = sf::Vector2f(offset, tilePosition.y + MINE_SIZE + offset);
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





